/*
 * EquationsEulerPassiveScalar.h
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_EQUATIONSEULERPASSIVESCALAR_H_
#define SRC_EQUATIONSEULERPASSIVESCALAR_H_

#include "Equations.h"

class EquationsEulerPassiveScalar: public Equations {
public:
	EquationsEulerPassiveScalar(double gamma) : gamma(gamma) {};
	virtual ~EquationsEulerPassiveScalar();

	static const int DENS   = 0;
	static const int XMOM   = 1;
	static const int ENERGY = 2;
	static const int PASS   = 3;

	double gamma;
	double* getFlux(std::vector<double>& quantities) override;
	double getMaxAbsEigenvalue(std::vector<double>& quantities) override;
	double totalEnergy(double p, double rhoV2);
	double getPressure(double e, double rhoV2);
	double getSoundSpeed(std::vector<double>& quantities);
};

#endif /* SRC_EQUATIONSEULERPASSIVESCALAR_H_ */
