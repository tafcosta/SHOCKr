/*
 * EquationsEulerCooling.cpp
 *
 *  Created on: 13 Feb 2024
 *      Author: ntc132
 */

#include <iostream>
#include <cstdio>

#include "EquationsEulerCooling.h"
#include "Grid.h"

void EquationsEulerCooling::doCooling(std::vector<double>& quantities, double dt){

	double temperatureOld = getTemperatureInternalUnits(quantities);
	double pressureNew, temperatureNew;

	temperatureNew = getInverseTemporalEvolutionFunction(getTemporalEvolutionFunction(temperatureOld) + temperatureOld/temperatureRef * coolingRate(temperatureRef)/coolingRate(temperatureOld) * dt/getCoolingTime(temperatureOld));
	pressureNew    = temperatureNew * quantities[DENS];

	quantities[ENERGY] = EquationsEuler::totalEnergy(pressureNew, std::pow(quantities[XMOM], 2.) / quantities[DENS]);

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

void EquationsEulerCooling::postProcessor(std::vector<double>& quantities, double dt){
	doCooling(quantities, dt);
}

EquationsEulerCooling::~EquationsEulerCooling() {
	// TODO Auto-generated destructor stub
}

