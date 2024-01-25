/*
 * RiemannSolverHLLC.h
 *
 *  Created on: 20 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_RIEMANNSOLVERHLLC_H_
#define SRC_RIEMANNSOLVERHLLC_H_

#include "RiemannSolver.h"
#include "EquationsEuler.h"

class RiemannSolverHLLC: public RiemannSolver {
public:

	RiemannSolverHLLC(Grid& grid, EquationsEuler& equations) : RiemannSolver(grid, equations) {};

	virtual std::vector<double> numericalFlux(std::vector<double>& quantitiesLeft, std::vector<double>& quantitiesRight) override;
	virtual ~RiemannSolverHLLC();
protected:
	void setMaxSpeed(double sLeft, double sRight);
};

#endif /* SRC_RIEMANNSOLVERHLLC_H_ */
