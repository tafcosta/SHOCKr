/*
 * EquationsEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "EquationsEulerPassiveScalar.h"

double* EquationsEulerPassiveScalar::getFlux(std::vector<double>& quantities) {
	double* flux = new double[nCons()];
	double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
	double p     = getPressure(quantities[ENERGY], rhoV2);

	flux[DENS]   = quantities[XMOM];
	flux[XMOM]   = rhoV2 + p;
	flux[ENERGY] = (p + quantities[ENERGY]) * quantities[XMOM] / quantities[DENS];
	flux[PASS]   = quantities[PASS] * quantities[XMOM] / quantities[DENS];

	return flux;
}

int EquationsEulerPassiveScalar::nCons(void){
	return 4;
}

EquationsEulerPassiveScalar::~EquationsEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

