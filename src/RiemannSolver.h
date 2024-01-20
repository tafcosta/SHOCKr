/*
 * RiemannSolver.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_RIEMANNSOLVER_H_
#define SRC_RIEMANNSOLVER_H_

#include "Equations.h"
#include "Grid.h"

class RiemannSolver {
public:
	RiemannSolver(Grid& grid, Equations& equations);
	virtual ~RiemannSolver();

	Grid& grid;
	Equations& equations;

	double maxSpeed;
	virtual void setFluxes() {};
};

#endif /* SRC_RIEMANNSOLVER_H_ */
