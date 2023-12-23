/*
 * EquationsEuler.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_EQUATIONSEULER_H_
#define SRC_EQUATIONSEULER_H_

#include "EquationsEuler.h"
#include "Equations.h"
#include "Grid.h"

class EquationsEuler: public Equations {
public:
	EquationsEuler(double gamma) : gamma(gamma){};
	virtual ~EquationsEuler();

	double totalEnergy(double p, double rhoV2){
		double totalEnergy = p / (gamma - 1) + 0.5 * rhoV2;
		return totalEnergy;
	}

	double getPressure(double e, double rhoV2){
		double p = (gamma - 1) * (e - 0.5 * rhoV2);
		return p;
	}

	double getSoundSpeed(std::vector<double>& quantities){
		double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
		double p = getPressure(quantities[ENERGY], rhoV2);
		double rho = quantities[DENS];

		return sqrt(gamma * p / rho);
	}

	static const int DENS   = 0;
	static const int XMOM   = 1;
	static const int ENERGY = 2;

	double gamma;
	double* getFlux(std::vector<double>& quantities) override;
	double getMaxAbsEigenvalue(std::vector<double>& quantities) override;
};

#endif /* SRC_EQUATIONSEULER_H_ */
