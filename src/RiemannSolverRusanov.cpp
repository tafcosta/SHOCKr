/*
 * RiemannSolverRusanov.cpp
 *
 *  Created on: 20 Jan 2024
 *      Author: ntc132
 */

#include "RiemannSolverRusanov.h"

void RiemannSolverRusanov::setFluxes(){
	double lambda = 0.;
	double* flux_i;
	double* flux_j;
	std::vector<double> flux_vector(equations.nCons());

	for(int i = grid.minXIndex; i <= (grid.maxXIndex + 1); i++)
	{
		flux_i = equations.getFlux(grid.quantities[i - 1]);
		flux_j = equations.getFlux(grid.quantities[i]);

		lambda = std::max(equations.getMaxAbsEigenvalue(grid.quantities[i]), equations.getMaxAbsEigenvalue(grid.quantities[i - 1]));

		for(int k = 0; k < equations.nCons(); k++)
			flux_vector[k] = 0.5 * (flux_i[k] + flux_j[k]) - 0.5 * (grid.quantities[i][k] - grid.quantities[i - 1][k]) * lambda;

		grid.fluxes[i] = flux_vector;

		if(maxSpeed < lambda)
			maxSpeed = lambda;
	}
}

RiemannSolverRusanov::~RiemannSolverRusanov() {
	// TODO Auto-generated destructor stub
}

