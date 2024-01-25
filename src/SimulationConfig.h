/*
 * SimulationConfig.h
 *
 *  Created on: 25 Jan 2024
 *      Author: Tiago Costa
 */

#ifndef SRC_SIMULATIONCONFIG_H_
#define SRC_SIMULATIONCONFIG_H_

#include <fstream>
#include <sstream>
#include <string>

class SimulationConfig {
public:
    // Simulation parameters
    double maxTime;
    double outputTimeInterval;
    std::string outputFilename;
    std::string outputEnergy;

    // Grid parameters
    double gridMin;
    double gridMax;
    int gridNcell;
    int gridNGhost;

    // Background parameters
    double bgDensity, bgVel, bgPressure;

    // Wind parameters
    double windDensity, windVel, windPressure;

    SimulationConfig(const std::string& configFile);
    virtual ~SimulationConfig();

private:
    void readConfig(const std::string& configFile);
};

#endif /* SRC_SIMULATIONCONFIG_H_ */
