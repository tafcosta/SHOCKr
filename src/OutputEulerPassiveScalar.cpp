/*
 * OutputEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: Tiago Costa
 */

#include "EquationsEulerPassiveScalar.h"
#include "OutputEulerPassiveScalar.h"

#include <cmath>
#include <fstream>
#include <string>
#include <iostream>

void OutputEulerPassiveScalar::makeOutput(const std::string& filename, double time){
    std::ofstream outputFile(filename, std::ios_base::app);
    std::ofstream outputFileEnergy("energy.txt", std::ios_base::app);

    auto* eq = static_cast<EquationsEulerPassiveScalar*>(&equations);

    double thermalEnergy     = 0.0;
    double windThermalEnergy = 0.0;
    double windKineticEnergy = 0.0;
    double kineticEnergy     = 0.0;

    double contactPosition   = grid.xmin;
    bool foundContact        = false;

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid.maxXIndex; i++) {

        const double dens   = grid.quantities[i][EquationsEulerPassiveScalar::DENS];
        if (dens <= 0.0)
            throw std::runtime_error("Non-positive density encountered in output.");

        const double xmom   = grid.quantities[i][EquationsEulerPassiveScalar::XMOM];
        const double pass   = grid.quantities[i][EquationsEulerPassiveScalar::PASS];

        const double rL = grid.getX(i) - 0.5 * grid.dx;
        const double rR = grid.getX(i) + 0.5 * grid.dx;
        const double dV = (4.0 / 3.0) * M_PI * (rR*rR*rR - rL*rL*rL);

        const double rhoV2    = xmom * xmom / dens;
        const double p        = eq->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2);
        const double v        = xmom / dens;
        const double passFrac = pass / dens;

        if (passFrac > 0.5) {
            contactPosition = grid.getX(i);
            foundContact = true;
        }

        if (v > 0.1) {
            if (passFrac < 1.e-5) {
                thermalEnergy += p / (eq->gamma - 1.0) * dV;
                kineticEnergy += 0.5 * rhoV2 * dV;
            } else {
                windThermalEnergy += p / (eq->gamma - 1.0) * dV;
                windKineticEnergy += 0.5 * rhoV2 * dV;
            }
        }

        outputFile << grid.getX(i) << " "
                   << dens << " "
                   << v << " "
                   << p << " "
                   << pass << '\n';
    }

    outputFile << '\n' << '\n';

    outputFileEnergy << time << " "
                     << (foundContact ? contactPosition - grid.xmin : 0.0) << " "
                     << windKineticEnergy << " "
                     << windThermalEnergy << " "
                     << kineticEnergy << " "
                     << thermalEnergy << '\n';

    const double boundaryDens = grid.quantities[grid.maxXIndex][EquationsEulerPassiveScalar::DENS];
    const double boundaryVel =
        grid.quantities[grid.maxXIndex][EquationsEulerPassiveScalar::XMOM] / boundaryDens;

    if (boundaryDens > 0.0 && boundaryVel > 1.e-1) {
        std::cout << boundaryVel << std::endl;
        throw std::runtime_error("Error: Contact has left domain. Stop.");
    }
}

OutputEulerPassiveScalar::~OutputEulerPassiveScalar() {

}

