/*
 * RiemannSolverRusanov.h
 *
 *  Created on: 20 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_RIEMANNSOLVERRUSANOV_H_
#define SRC_RIEMANNSOLVERRUSANOV_H_

#include "RiemannSolver.h"

class RiemannSolverRusanov: public RiemannSolver {
public:
	RiemannSolverRusanov(Grid& grid, Equations& equations) : RiemannSolver(grid, equations){};
	virtual ~RiemannSolverRusanov();

	virtual void setFluxes() override;
};

#endif /* SRC_RIEMANNSOLVERRUSANOV_H_ */
