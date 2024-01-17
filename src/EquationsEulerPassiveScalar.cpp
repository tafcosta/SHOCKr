/*
 * EquationsEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "EquationsEulerPassiveScalar.h"

double* EquationsEulerPassiveScalar::getFlux(std::vector<double>& quantities) {
	double* flux = new double[nCons()];
	double* eulerFlux = EquationsEuler::getFlux(quantities);

	flux[DENS]   = eulerFlux[DENS];
	flux[XMOM]   = eulerFlux[XMOM];
	flux[ENERGY] = eulerFlux[ENERGY];
	flux[PASS]   = quantities[PASS] * quantities[XMOM] / quantities[DENS];

	delete[] eulerFlux;

	return flux;
}

int EquationsEulerPassiveScalar::nCons(void){
	return EquationsEuler::nCons() + 1;
}

EquationsEulerPassiveScalar::~EquationsEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

