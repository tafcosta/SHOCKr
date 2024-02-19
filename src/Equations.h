/*
 * Equations.h
 *
 *  Created on: 21 Dec 2023
 *      Author: ntc132
 */

#include <vector>

#ifndef SRC_EQUATIONS_H_
#define SRC_EQUATIONS_H_

#include "SimulationConfig.h"

class Equations {
public:
	Equations();
	virtual ~Equations();

	virtual int nCons(void);

	virtual double  getMaxAbsEigenvalue(std::vector<double>& quantities){return 0.;};
	virtual double* getFlux(std::vector<double>& quantities){return 0;};
	virtual void postProcessor(std::vector<double>& quantities, double dt){};
	virtual void preProcessor(){};

};

#endif /* SRC_EQUATIONS_H_ */
