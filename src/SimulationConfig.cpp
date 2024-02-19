/*
 * SimulationConfig.cpp
 *
 *  Created on: 25 Jan 2024
 *      Author: Tiago Costa
 */

#include <fstream>
#include <sstream>
#include <string>
#include "SimulationConfig.h"

SimulationConfig::SimulationConfig(const std::string& configFile) {
	readConfig(configFile);
}

void SimulationConfig::readConfig(const std::string& configFile) {
    std::ifstream file(configFile);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        if (!(iss >> key >> value))
            continue;

        if (key == "maxTime") {
            maxTime = std::stod(value);
        } else if (key == "outputTimeInterval") {
            outputTimeInterval = std::stod(value);
        } else if (key == "gridMin") {
            gridMin = std::stod(value);
        } else if (key == "gridMax") {
        	gridMax = std::stod(value);
        } else if (key == "NumberCells") {
        	gridNcell = std::stoi(value);
        } else if (key == "NumberGhostCells") {
        	gridNGhost = std::stoi(value);
        } else if (key == "bgDensity") {
        	bgDensity = std::stod(value);
        } else if (key == "bgVel") {
        	bgVel = std::stod(value);
        } else if (key == "bgPressure") {
        	bgPressure = std::stod(value);
        } else if (key == "windDensity") {
        	windDensity = std::stod(value);
        } else if (key == "windVel") {
        	windVel = std::stod(value);
        } else if (key == "windPressure") {
        	windPressure = std::stod(value);
        } else if (key == "unitMassInCgs") {
        	unitMassInCgs = std::stod(value);
        } else if (key == "unitVelocityInCgs") {
        	unitVelocityInCgs = std::stod(value);
        } else if (key == "unitLengthInCgs") {
        	unitLengthInCgs = std::stod(value);
        }
    }
}


SimulationConfig::~SimulationConfig() {
	// TODO Auto-generated destructor stub
}



