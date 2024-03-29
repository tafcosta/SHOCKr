/*
 * OutputEuler.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "EquationsEuler.h"
#include "OutputEuler.h"
#include <fstream>
#include <string>
#include <iostream>

void OutputEuler::makeOutput(const std::string& filename, double time){
    std::ofstream outputFile(filename, std::ios_base::app);
    double rhoV2, p, gamma;

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid.maxXIndex; i++) {
    	rhoV2 = grid.quantities[i][EquationsEuler::XMOM] * grid.quantities[i][EquationsEuler::XMOM] / grid.quantities[i][EquationsEuler::DENS];
    	p = (static_cast<EquationsEuler*>(&equations))->getPressure(grid.quantities[i][EquationsEuler::ENERGY], rhoV2);
    	gamma = (static_cast<EquationsEuler*>(&equations))->gamma;
        outputFile << grid.getX(i) << " " << grid.quantities[i][EquationsEuler::DENS] << " " << grid.quantities[i][EquationsEuler::XMOM] / grid.quantities[i][EquationsEuler::DENS] << " " << p << " " << p/grid.quantities[i][EquationsEuler::DENS] << std::endl;
    }

    outputFile << " " << std::endl;
    outputFile << " " << std::endl;
    outputFile.close();
}

OutputEuler::~OutputEuler() {
	// TODO Auto-generated destructor stub
}

