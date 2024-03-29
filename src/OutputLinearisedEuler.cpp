/*
 * OutputLinearisedEuler.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "EquationsLinearisedEuler.h"
#include "OutputLinearisedEuler.h"
#include <fstream>
#include <string>
#include <iostream>

void OutputLinearisedEuler::makeOutput(const std::string& filename, double time){
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid.maxXIndex; i++) {
        outputFile << grid.getX(i) << " " << grid.quantities[i][EquationsLinearisedEuler::DENS] << " " << grid.quantities[i][EquationsLinearisedEuler::VEL] << " " << grid.quantities[i][EquationsLinearisedEuler::PRESS] << std::endl;
    }

    outputFile.close();
}

OutputLinearisedEuler::~OutputLinearisedEuler() {
	// TODO Auto-generated destructor stub
}

