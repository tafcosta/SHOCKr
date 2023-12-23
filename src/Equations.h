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

	static const int DENS   = 0;
	static const int XMOM   = 1;
	static const int ENERGY = 2;
	static const int nCons  = 3;
	double gamma;

	virtual double getMaxAbsEigenvalue(std::vector<double>& quantities){return 0.;};
	virtual double* getFlux(std::vector<double>& quantities){return 0;};

};

#endif /* SRC_EQUATIONS_H_ */
