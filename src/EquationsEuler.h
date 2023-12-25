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

class EquationsEuler: public Equations {
public:
	EquationsEuler(double gamma) : gamma(gamma) {};
	virtual ~EquationsEuler();

	static const int DENS   = 0;
	static const int XMOM   = 1;
	static const int ENERGY = 2;

	double gamma;
	double* getFlux(std::vector<double>& quantities) override;
	double getMaxAbsEigenvalue(std::vector<double>& quantities) override;
	double totalEnergy(double p, double rhoV2);
	double getPressure(double e, double rhoV2);
	double getSoundSpeed(std::vector<double>& quantities);
};

#endif /* SRC_EQUATIONSEULER_H_ */
