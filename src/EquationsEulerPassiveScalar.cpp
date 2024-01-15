/*
 * EquationsEulerPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "EquationsEulerPassiveScalar.h"

double EquationsEulerPassiveScalar::getMaxAbsEigenvalue(std::vector<double>& quantities) {
	double u, cs;

	cs   = getSoundSpeed(quantities);
	u    = quantities[EquationsEulerPassiveScalar::XMOM]/quantities[EquationsEulerPassiveScalar::DENS];

	return abs(u) + abs(cs);
}

double* EquationsEulerPassiveScalar::getFlux(std::vector<double>& quantities) {
	double* flux = new double[nCons];
	double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
	double p     = getPressure(quantities[ENERGY], rhoV2);

	flux[DENS]   = quantities[XMOM];
	flux[XMOM]   = rhoV2 + p;
	flux[ENERGY] = (p + quantities[ENERGY]) * quantities[XMOM] / quantities[DENS];
	flux[PASS]   = quantities[PASS] * quantities[XMOM] / quantities[DENS];

	return flux;
}

double EquationsEulerPassiveScalar::totalEnergy(double p, double rhoV2){
	return p / (gamma - 1) + 0.5 * rhoV2;
}

double EquationsEulerPassiveScalar::getPressure(double e, double rhoV2){
	return (gamma - 1) * (e - 0.5 * rhoV2);
}

double EquationsEulerPassiveScalar::getSoundSpeed(std::vector<double>& quantities){
	double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
	double p = getPressure(quantities[ENERGY], rhoV2);
	double rho = quantities[DENS];

	return sqrt(gamma * p / rho);
}

EquationsEulerPassiveScalar::~EquationsEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

