/*
 * GasProfileNFW.cpp
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#include "GasProfileNFW.h"
#include <cmath>
#include <iostream>

GasProfileNFW::GasProfileNFW(double haloMass, double haloConcentration, double baryonFraction, double unitLengthInCgs, double unitMassInCgs, double unitTimeInCgs) : baryonFraction(baryonFraction){
	const double G    = 6.67430e-8;
	const double Mpc  = 3.085677581e24;
	const double km   = 1.0e5;
	const double Msun = 1.98847e33;
	const double H0   = 70.0 * km / Mpc;

    const double rhoCrit = 3.0 * H0 * H0 / (8.0 * M_PI * G);
    const double M200 = haloMass * Msun;
    const double R200 = std::cbrt(3.0 * M200 / (4.0 * M_PI * 200.0 * rhoCrit));
    const double rs   = R200 / haloConcentration;

    const double delta_c = (200.0/3.0) * std::pow(haloConcentration,3) / ( std::log(1.0+haloConcentration) - haloConcentration/(1.0+haloConcentration) );
    const double rho_s   = delta_c * rhoCrit;

    rScale   = rs / unitLengthInCgs;
    rhoScale = rho_s / (unitMassInCgs / std::pow(unitLengthInCgs, 3));
    Gcode    = G * unitMassInCgs * unitTimeInCgs * unitTimeInCgs / std::pow(unitLengthInCgs, 3);
}

double GasProfileNFW::density(double r) const{
    const double x = r/rScale;
    return baryonFraction * rhoScale/(x*(1.0+x)*(1.0+x));
}

double GasProfileNFW::pressure(double r) const
{
    const double x = r / rScale;

    if (x < 1.0e-8)
    {
        return 2.0 * M_PI
             * Gcode
             * rhoScale * rhoScale
             * rScale * rScale;
    }

    const double f = std::log(1.0 + x) / x;

    return 2.0 * M_PI * Gcode * rhoScale * rhoScale * rScale * rScale * f * f;
}



double GasProfileNFW::velocity(double) const{
    return 0.0;
}

GasProfileNFW::~GasProfileNFW() {
	// TODO Auto-generated destructor stub
}

