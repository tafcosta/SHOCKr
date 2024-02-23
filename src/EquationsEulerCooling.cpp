/*
 * EquationsEulerCooling.cpp
 *
 *  Created on: 13 Feb 2024
 *      Author: ntc132
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "EquationsEulerCooling.h"

void EquationsEulerCooling::doCooling(std::vector<double>& quantities, double dt){
	double dtPhysical = dt * unitL/unitV;
	double temperatureOld = getTemperaturePhysicalUnits(quantities);
	double temperatureNew = std::max(tempMin, getInverseTemporalEvolutionFunction(temperatureOld, getTemporalEvolutionFunction(temperatureOld) + temperatureOld/temperatureRef * coolingRate(temperatureRef)/coolingRate(temperatureOld) * dtPhysical/getCoolingTime(quantities)));
	double temperatureNewInternalUnits = temperatureNew * BOLTZMANN_CONSTANT / PROTON_MASS / std::pow(unitV, 2.);

	//std::cout << temperatureNew << std::endl;

	quantities[ENERGY] = EquationsEuler::totalEnergy(temperatureNewInternalUnits * quantities[DENS], std::pow(quantities[XMOM], 2.) / quantities[DENS]);

}

double EquationsEulerCooling::coolingRate(double temperature){
	int k;
	for(k = numTemperatureEdges - 1; temperature < temperatureBins[k]; k--){};

	return std::max(coolingRateEdgeBin[k + 1] * std::pow((temperatureBins[k + 1] / temperatureRef), slope[k]), 1.e-30);
}

double EquationsEulerCooling::getCoolingTime(std::vector<double>& quantities){
	double temperature = getTemperaturePhysicalUnits(quantities);
	double densityPhysical = quantities[DENS] * PROTON_MASS;

	return std::pow(((gamma - 1) * coolingRate(temperature) * densityPhysical)/ (BOLTZMANN_CONSTANT * PROTON_MASS * temperature), -1);
}

double EquationsEulerCooling::getTemporalEvolutionFunction(double temperature){

	int k;
	double TemporalEvolutionFunction;
	double integrationConstant = 0.;

	for(k = numTemperatureEdges - 1; temperature < temperatureBins[k]; k--){
		if(slope[k] != 1)
			integrationConstant -= 1./(1 - slope[k]) * coolingRateRef/coolingRateEdgeBin[k] * temperatureBins[k]/temperatureRef * (1 - std::pow(temperatureBins[k] / temperatureBins[k+1], slope[k] - 1));
		else
			integrationConstant -= coolingRateRef/coolingRateEdgeBin[k] * temperatureBins[k]/temperatureRef * std::log(temperatureBins[k] / temperatureBins[k+1]);
	}

	if(slope[k] != 1)
		TemporalEvolutionFunction = 1./(1 - slope[k]) * coolingRateRef/coolingRateEdgeBin[k] * temperatureBins[k]/temperatureRef * (1 - std::pow(temperatureBins[k] / temperature, slope[k] - 1));
	else
		TemporalEvolutionFunction = coolingRateEdgeBin[k] * temperatureBins[k]/temperatureRef * std::log(temperatureBins[k] / temperature);

	return TemporalEvolutionFunction + integrationConstant;
}

double EquationsEulerCooling::getInverseTemporalEvolutionFunction(double temperature, double TemporalEvolutionFunction){
	int k;
	double integrationConstant = 0.;
	double InverseTemporalEvolutionFunction;

	for(k = numTemperatureEdges - 1; temperature < temperatureBins[k]; k--){
		if(slope[k] != 1)
			integrationConstant -= 1./(1 - slope[k]) * coolingRateRef/coolingRateEdgeBin[k] * temperatureBins[k]/temperatureRef * (1 - std::pow(temperatureBins[k] / temperatureBins[k+1], slope[k] - 1));
		else
			integrationConstant -= coolingRateRef/coolingRateEdgeBin[k] * temperatureBins[k]/temperatureRef * std::log(temperatureBins[k] / temperatureBins[k+1]);
	}

	if(slope[k] != 1)
		InverseTemporalEvolutionFunction = temperatureBins[k] * std::pow((1 - (1 - slope[k]) * coolingRateEdgeBin[k]/coolingRateRef * temperatureRef/temperatureBins[k] * (TemporalEvolutionFunction - integrationConstant)), 1./(1 - slope[k]));
	else
		InverseTemporalEvolutionFunction = temperatureBins[k] * std::exp(-coolingRateEdgeBin[k]/coolingRateRef * temperatureRef/temperatureBins[k] * (TemporalEvolutionFunction - integrationConstant));

	return InverseTemporalEvolutionFunction;

}

double EquationsEulerCooling::getTemperaturePhysicalUnits(std::vector<double>& quantities){
	return EquationsEuler::getPressure(quantities) / quantities[DENS] * std::pow(unitV, 2.) * PROTON_MASS / BOLTZMANN_CONSTANT;
}

void EquationsEulerCooling::preProcessor(){
    std::ifstream inputFile("tables/CoolingTable.txt");

    if (!inputFile.is_open())
        throw std::runtime_error("Error: Cannot find cooling table.");

    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        double value;
        std::vector<double> row;

        while (ss >> value) {
            row.push_back(value);
            ss.ignore();
        }

        coolingTable.push_back(row);
    }

    inputFile.close();

    for (size_t i = 0; i < coolingTable.size(); ++i) {
        temperatureBins.push_back(std::pow(10, coolingTable[i][0]));
        coolingRateEdgeBin.push_back(std::pow(10, coolingTable[i][1]));
        slope.push_back(coolingTable[i][2]);
    }

    numTemperatureEdges = static_cast<int>(coolingTable.size());
    temperatureRef      = std::pow(10, std::log10(temperatureBins[numTemperatureEdges - 1])    + (std::log10(temperatureBins[1]) - std::log10(temperatureBins[0])));
    coolingRateRef      = std::pow(10, std::log10(coolingRateEdgeBin[numTemperatureEdges - 1]) + slope[numTemperatureEdges - 1]  * (std::log10(temperatureRef) - std::log10(temperatureBins[numTemperatureEdges - 1])));

    temperatureBins.push_back(temperatureRef);
    coolingRateEdgeBin.push_back(coolingRateRef);
}

void EquationsEulerCooling::postProcessor(std::vector<double>& quantities, double dt){
	doCooling(quantities, dt);
}

EquationsEulerCooling::~EquationsEulerCooling() {
}

