/*
 * OutputEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
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

    double p, rhoV2;
    double thermalEnergy = 0.;
    double totalEnergy   = 0.;
    double kineticEnergy = 0.;
    double contactPosition, v;

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid.maxXIndex; i++) {
    	rhoV2 = grid.quantities[i][EquationsEulerPassiveScalar::XMOM] * grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	p = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2);
    	v = grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS];

    	if(grid.quantities[i][EquationsEulerPassiveScalar::PASS]/grid.quantities[i][EquationsEulerPassiveScalar::DENS] > 1.e-5)
    		contactPosition = grid.getX(i);

    	if(grid.quantities[i][EquationsEulerPassiveScalar::PASS]/grid.quantities[i][EquationsEulerPassiveScalar::DENS] < 1.e-5){
    		thermalEnergy += p / ((static_cast<EquationsEulerPassiveScalar*>(&equations))->gamma - 1) * std::pow(grid.getX(i),2.);
    		totalEnergy   += grid.quantities[i][EquationsEulerPassiveScalar::ENERGY] * std::pow(grid.getX(i),2.);
    		kineticEnergy += 0.5 * rhoV2 * 4./3 * 3.1415 * (std::pow(grid.getX(i) + grid.dx/2, 3.) - std::pow(grid.getX(i) - grid.dx/2, 3.));
    	}

        outputFile << grid.getX(i) << " " << grid.quantities[i][EquationsEulerPassiveScalar::DENS] << " " << grid.quantities[i][EquationsEulerPassiveScalar::XMOM]/grid.quantities[i][EquationsEulerPassiveScalar::DENS] << " " << p << " " << grid.quantities[i][EquationsEulerPassiveScalar::PASS]/grid.quantities[i][EquationsEulerPassiveScalar::DENS]<< std::endl;
    }

    outputFile << " " << std::endl;
    outputFile << " " << std::endl;
    outputFile.close();

    if (!outputFileEnergy.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    //outputFileEnergy << time << " " << contactPosition - grid.xmin << " " << thermalEnergy/kineticEnergy << std::endl;
    outputFileEnergy << time << " " << contactPosition - grid.xmin << " " << kineticEnergy/(502640000.0 * time) << std::endl;

    outputFileEnergy.close();
}

OutputEulerPassiveScalar::~OutputEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

