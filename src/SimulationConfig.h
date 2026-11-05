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

    // Grid parameters
    double gridMin;
    double gridMax;
    int gridNcell;
    int gridNGhost;

    // Background parameters
    double bgDensity, bgVel, bgPressure;
    double powerLawExponent = 0.0;
    double powerLawRadius   = -1.0;
    std::string gasProfile  = "nfw";
    double haloConcentration, haloMass, baryonFraction;
    double redshift = 0.0;
    double sisSigma    = 200.0;            // SIS velocity dispersion, km/s (code velocity)
    double gasFraction = 0.16;             // SIS gas fraction f_g

    // Gravity
    int    gravity       = 1;
    double blackHoleMass = 1.e7;          // code units

    // Compton cooling by the AGN radiation field
    int    comptonCooling     = 0;        // 0 = off, 1 = cooling and heating, 2 = cooling only
    double agnLuminosity      = 0.0;      // erg/s
    double comptonTemperature = 2.e7;     // K
    int    comptonRelativistic = 0;       // 1 = include relativistic correction for hot electrons

    // Outer boundary: "zerogradient" (default) or "fixed" (ghost cells stay at the initial profile)
    std::string outerBoundary = "zerogradient";

    // Inner boundary: "wind" (default, wind enters through the ghost cells) or
    // "injection" (reflecting wall at r_in, wind added as a source in the first
    // injectionCells cells, see WindInjection.h)
    std::string innerBoundary = "wind";
    int    injectionCells     = 4;

    // Artificial cooling test (see ArtificialCooling.h): 0 = off, 1 = wind,
    // 2 = wind and swept-up shell. haloPressurePerDensity <= 0 means sisSigma^2
    int    artificialCooling      = 0;
    double haloPressurePerDensity = 0.0;

    // Wind parameters
    double windDensity, windVel, windPressure;

    // Units
    double unitLengthInCgs, unitMassInCgs, unitVelocityInCgs;

    // Output File
    std::string outputFile;

    SimulationConfig(const std::string& configFile);
    virtual ~SimulationConfig();

private:
    void readConfig(const std::string& configFile);
};

#endif /* SRC_SIMULATIONCONFIG_H_ */
