/*
 * GasProfileNFW.cpp
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#include "GasProfileNFW.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

GasProfileNFW::GasProfileNFW(double haloMass,
                             double haloConcentration,
                             double baryonFraction,
                             double unitLengthInCgs,
                             double unitMassInCgs,
                             double unitTimeInCgs)
: baryonFraction(baryonFraction)
{
    const double G    = 6.67430e-8;
    const double Mpc  = 3.085677581e24;
    const double km   = 1.0e5;
    const double Msun = 1.98847e33;
    const double H0   = 70.0 * km / Mpc;

    const double rhoCrit = 3.0 * H0 * H0 / (8.0 * M_PI * G);
    const double M200    = haloMass * Msun;
    const double R200    = std::cbrt(3.0 * M200 / (4.0 * M_PI * 200.0 * rhoCrit));

    const double rs = R200 / haloConcentration;
    const double delta_c = (200.0 / 3.0) * std::pow(haloConcentration,3) / (std::log(1.0 + haloConcentration)  - haloConcentration/(1.0 + haloConcentration));
    const double rho_s = delta_c * rhoCrit;
    const double unitDensity = unitMassInCgs / std::pow(unitLengthInCgs,3);

    rScale   = rs / unitLengthInCgs;
    rhoScale = baryonFraction * rho_s / unitDensity;
    Gcode    = G * unitMassInCgs * unitTimeInCgs * unitTimeInCgs / std::pow(unitLengthInCgs,3);

    //--------------------------------------------------
    // Build pressure table
    //--------------------------------------------------

    const int N = 2000;

    radiusTable.resize(N);
    pressureTable.resize(N);

    const double rmin = 1.0e-6 * rScale;
    const double rmax = 1.0e3 * rScale;

    const double dlogr =
        std::log(rmax/rmin)/(N-1);

    for(int i=0;i<N;i++)
        radiusTable[i] =
            rmin * std::exp(i*dlogr);

    pressureTable[N-1]=0.0;

    for(int i=N-2;i>=0;i--)
    {
        const double r1 = radiusTable[i];
        const double r2 = radiusTable[i+1];

        auto rhs = [&](double r)
        {
            const double x = r/rScale;

            const double rho = rhoScale / (x*(1.0+x)*(1.0+x));
            const double rhoDM = rhoScale / baryonFraction;
            const double M = 4.0 * M_PI * rhoDM * std::pow(rScale,3) * (std::log(1.0+x) - x/(1.0+x));

            return rho * Gcode * M / (r * r);
        };

        pressureTable[i] =
            pressureTable[i+1]
            +0.5*(rhs(r1)+rhs(r2))
             *(r2-r1);
    }
}

double GasProfileNFW::density(double r) const{
    const double x = r/rScale;

    return rhoScale /
           (x*(1.0+x)*(1.0+x));
}

double GasProfileNFW::pressure(double r) const{
    if(r<=radiusTable.front())
        return pressureTable.front();

    if(r>=radiusTable.back())
        return pressureTable.back();

    auto it = std::lower_bound(radiusTable.begin(),
                         radiusTable.end(),
                         r);

    std::size_t i = std::distance(radiusTable.begin(),it);

    const double r1 = radiusTable[i-1];
    const double r2 = radiusTable[i];

    const double p1 = pressureTable[i-1];
    const double p2 = pressureTable[i];

    return p1 +
           (p2-p1)*(r-r1)/(r2-r1);
}

double GasProfileNFW::velocity(double) const{
    return 0.0;
}

double GasProfileNFW::enclosedMass(double r) const{
    const double x = r / rScale;
    return 4.0 * M_PI * rhoScale * std::pow(rScale,3) * (std::log(1.0 + x) - x/(1.0 + x));
}

GasProfileNFW::~GasProfileNFW(){}
