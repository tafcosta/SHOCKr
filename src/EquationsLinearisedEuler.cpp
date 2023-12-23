/*
 * EquationsLinearisedEuler.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "EquationsLinearisedEuler.h"
#include "Equations.h"

double EquationsLinearisedEuler::getMaxAbsEigenvalue(std::vector<double>& quantities) {
	return std::max(abs(BgDensity), std::max(abs(BgVel), abs(BgSoundSpeed)));
}

double* EquationsLinearisedEuler::getFlux(std::vector<double>& quantities) {
	double* flux = new double[nCons];

	flux[DENS]  = BgVel * quantities[DENS] + BgDensity * quantities[VEL];
	flux[VEL]   = BgVel * quantities[VEL] + quantities[PRESS] / BgDensity;
	flux[PRESS] = BgVel * quantities[PRESS] + BgDensity * pow(BgSoundSpeed, 2.) * quantities[VEL];

	return flux;
}

EquationsLinearisedEuler::~EquationsLinearisedEuler() {
	// TODO Auto-generated destructor stub
}

