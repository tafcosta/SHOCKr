/*
 * EquationsEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "EquationsEulerPassiveScalar.h"

double* EquationsEulerPassiveScalar::getFlux(std::vector<double>& quantities) {
	double* flux = new double[nCons()];

	flux[PASS]   = quantities[PASS] * quantities[XMOM] / quantities[DENS];

	return flux;
}

EquationsEulerPassiveScalar::~EquationsEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

