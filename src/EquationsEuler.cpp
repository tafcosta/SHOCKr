/*
 * EquationsEuler.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "EquationsEuler.h"
#include "Equations.h"

double EquationsEuler::getMaxAbsEigenvalue(std::vector<double>& quantities) {
	double u, cs;

	cs   = getSoundSpeed(quantities);
	u    = quantities[EquationsEuler::XMOM]/quantities[EquationsEuler::DENS];

	return abs(u) + abs(cs);
}

double* EquationsEuler::getFlux(std::vector<double>& quantities) {
	double* flux = new double[nCons];
	double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
	double p     = getPressure(quantities[ENERGY], rhoV2);

	flux[DENS]   = quantities[XMOM];
	flux[XMOM]   = rhoV2 + p;
	flux[ENERGY] = (p + quantities[ENERGY]) * quantities[XMOM] / quantities[DENS];

	return flux;
}

EquationsEuler::~EquationsEuler() {
	// TODO Auto-generated destructor stub
}

