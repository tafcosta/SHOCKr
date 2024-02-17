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
#include "Grid.h"

void EquationsEulerCooling::doCooling(std::vector<double>& quantities, double dt){

	double temperatureOld = getTemperatureInternalUnits(quantities);
	double temperatureNew = getInverseTemporalEvolutionFunction(getTemporalEvolutionFunction(temperatureOld) + temperatureOld/temperatureRef * coolingRate(temperatureRef)/coolingRate(temperatureOld) * dt/getCoolingTime(temperatureOld));

	quantities[ENERGY] = EquationsEuler::totalEnergy(temperatureNew * quantities[DENS], std::pow(quantities[XMOM], 2.) / quantities[DENS]);

}

double EquationsEulerCooling::coolingRate(double temperature){
	double lambdaRef = 1;
	return std::max(lambdaRef * (temperature / temperatureRef), 1.e-30);
}

double EquationsEulerCooling::getCoolingTime(double temperature){
	return std::pow((gamma - 1) * coolingRate(temperature) / temperature, -1);
}

double EquationsEulerCooling::getTemporalEvolutionFunction(double temperature){
	return std::log(temperatureRef/temperature);
}

double EquationsEulerCooling::getInverseTemporalEvolutionFunction(double Y){
	return temperatureRef * std::exp(-Y);
}

double EquationsEulerCooling::getTemperatureInternalUnits(std::vector<double>& quantities){
	return EquationsEuler::getPressure(quantities) / quantities[DENS];
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
}

void EquationsEulerCooling::postProcessor(std::vector<double>& quantities, double dt){
	doCooling(quantities, dt);
}

EquationsEulerCooling::~EquationsEulerCooling() {
	// TODO Auto-generated destructor stub
}

