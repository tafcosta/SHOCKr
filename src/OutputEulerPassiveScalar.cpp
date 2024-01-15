/*
 * OutputEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "EquationsEulerPassiveScalar.h"
#include "OutputEulerPassiveScalar.h"
#include <fstream>
#include <string>
#include <iostream>

void OutputEulerPassiveScalar::makeOutput(const std::string& filename){
    std::ofstream outputFile(filename, std::ios_base::app);
    double rhoV2, p;

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid.maxXIndex; i++) {
    	rhoV2 = grid.quantities[i][EquationsEulerPassiveScalar::XMOM] * grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	p = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2);
        outputFile << grid.getX(i) << " " << grid.quantities[i][EquationsEulerPassiveScalar::PASS] << " " << p << std::endl;
    }

    outputFile << " " << std::endl;
    outputFile.close();
}

OutputEulerPassiveScalar::~OutputEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

