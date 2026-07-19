/*
 * SourceGravity.cpp
 *
 *  Created on: 27 Sept 2025
 *      Author: Tiago Costa
 */

#include "SourceGravity.h"
#include "SimulationDependencies.h"

std::vector<double> SourceGravity::getSource(std::vector<double>& quantities, double radialDistance){

	std::vector<double> res = std::vector<double>(equations.nCons(), 0.0);

	double acceleration = -Grav * enclosedMass(radialDistance) / (radialDistance * radialDistance);

	res[EquationsEuler::XMOM]   = quantities[EquationsEuler::DENS] * acceleration;
	res[EquationsEuler::ENERGY] = quantities[EquationsEuler::XMOM] * acceleration;

	return res;
}

double SourceGravity::enclosedMass(double radialDistance){
    double mGasEquivalent = 4.0 * M_PI * rhoBackground
    		* std::pow(grid.xmin, powerLawExponent) * std::pow(radialDistance, 3.0 - powerLawExponent) / ((3.0 - powerLawExponent) * gasFraction);

    return massBH + mGasEquivalent;
}


SourceGravity::~SourceGravity() {
	// TODO Auto-generated destructor stub
}

