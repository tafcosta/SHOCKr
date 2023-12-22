/*
 * Equations.h
 *
 *  Created on: 21 Dec 2023
 *      Author: ntc132
 */

#include <vector>

#ifndef SRC_EQUATIONS_H_
#define SRC_EQUATIONS_H_

class Equations {
public:
	Equations(double gamma);
	virtual ~Equations();

	static const int DENS = 0;
	static const int XMOM = 1;
	static const int ENERGY = 2;
	static const int nCons = 3;
	double gamma;

	double totalEnergy(double p, double rhoV2){
		double totalEnergy = p / (gamma - 1) + 0.5 * rhoV2;
		return totalEnergy;
	}

	double getPressure(double e, double rhoV2){
		double p = (gamma - 1) * (e - 0.5 * rhoV2);
		return p;
	}

	double* getFlux(std::vector<double>& quantities){
		double* flux = new double[nCons];
		double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
		double p     = getPressure(quantities[ENERGY], rhoV2);

		flux[DENS]   = quantities[XMOM];
		flux[XMOM]   = rhoV2 + p;
		flux[ENERGY] = (p + quantities[ENERGY]) * quantities[XMOM] / quantities[DENS];

		return flux;
	}

	double getSoundSpeed(std::vector<double>& quantities){
		double rhoV2 = quantities[XMOM] * quantities[XMOM] / quantities[DENS];
		double p = getPressure(quantities[ENERGY], rhoV2);
		double rho = quantities[DENS];

		return sqrt(gamma * p / rho);
	}
};

#endif /* SRC_EQUATIONS_H_ */
