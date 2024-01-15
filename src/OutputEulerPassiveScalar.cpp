/*
 * OutputEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "OutputEulerPassiveScalar.h"
#include "EquationsEulerPassiveScalar.h"
#include <fstream>
#include <string>
#include <iostream>

void OutputEulerPassiveScalar::makeOutput(const std::string& filename){
    std::ofstream outputFile(filename, std::ios_base::app);
    double rhoV2, p, gamma;

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid.maxXIndex; i++) {
    	rhoV2 = grid.quantities[i][EquationsEulerPassiveScalar::XMOM] * grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	p = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2);
    	gamma = (static_cast<EquationsEulerPassiveScalar*>(&equations))->gamma;
        outputFile << grid.getX(i) << " " << grid.quantities[i][EquationsEulerPassiveScalar::DENS] << " " << 0.5 * rhoV2 / (p / (gamma - 1) + 0.5 * rhoV2) << " " << grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS] << " " << p << std::endl;
    }

    outputFile << " " << std::endl;
    outputFile.close();
}

OutputEulerPassiveScalar::~OutputEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

