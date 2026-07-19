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

	double acceleration = -Grav * (massBH + gasProfile.enclosedMass(radialDistance)) / (radialDistance * radialDistance);

	res[EquationsEuler::XMOM]   = quantities[EquationsEuler::DENS] * acceleration;
	res[EquationsEuler::ENERGY] = quantities[EquationsEuler::XMOM] * acceleration;

	return res;
}


SourceGravity::~SourceGravity() {
	// TODO Auto-generated destructor stub
}

