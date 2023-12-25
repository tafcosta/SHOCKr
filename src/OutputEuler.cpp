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

void OutputEuler::makeOutput(const std::string& filename){
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid.maxXIndex; i++) {
        outputFile << grid.getX(i) << " " << grid.quantities[i][EquationsEuler::DENS] << " " << grid.quantities[i][EquationsEuler::XMOM]/grid.quantities[i][EquationsEuler::DENS] << " " << grid.quantities[i][EquationsEuler::ENERGY] << std::endl;
    }

    outputFile.close();
}

OutputEuler::~OutputEuler() {
	// TODO Auto-generated destructor stub
}

