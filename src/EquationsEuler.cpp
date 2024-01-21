/*
 * EquationsEuler.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "EquationsEuler.h"

#include <cstdlib>
#include <cmath>

double EquationsEuler::getMaxAbsEigenvalue(std::vector<double>& quantities) {
	double u, cs;

	cs   = getSoundSpeed(quantities);
	u    = quantities[EquationsEuler::XMOM]/quantities[EquationsEuler::DENS];

	return std::abs(u) + std::abs(cs);
}

double* EquationsEuler::getFlux(std::vector<double>& quantities) {
	double* flux = new double[nCons()];
	double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
	double p     = getPressure(quantities[ENERGY], rhoV2);

	flux[DENS]   = quantities[XMOM];
	flux[XMOM]   = rhoV2 + p;
	flux[ENERGY] = (p + quantities[ENERGY]) * quantities[XMOM] / quantities[DENS];

	return flux;
}

double EquationsEuler::totalEnergy(double p, double rhoV2){
	return p / (gamma - 1) + 0.5 * rhoV2;
}

double EquationsEuler::getPressure(double e, double rhoV2){
	return (gamma - 1) * (e - 0.5 * rhoV2);
}

double EquationsEuler::getSoundSpeed(std::vector<double>& quantities){
	double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
	double p = getPressure(quantities[ENERGY], rhoV2);
	double rho = quantities[DENS];

	return std::sqrt(gamma * p / rho);
}

EquationsEuler::~EquationsEuler() {
	// TODO Auto-generated destructor stub
}

