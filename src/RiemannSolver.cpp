/*
 * RiemannSolver.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"
#include "RiemannSolver.h"

void RiemannSolver::setFluxes(){
	double lambda = 0.;
	double* flux_i;
	double* flux_j;
	std::vector<double> flux_vector(Equations::nCons);

	for(int i = grid.minXIndex; i <= (grid.maxXIndex + 1); i++)
	{
		flux_i = equations.getFlux(grid.quantities[i - 1]);
		flux_j = equations.getFlux(grid.quantities[i]);

		lambda = std::max(equations.getMaxAbsEigenvalue(grid.quantities[i]), equations.getMaxAbsEigenvalue(grid.quantities[i - 1]));

		for(int k = 0; k < Equations::nCons; k++)
			flux_vector[k] = 0.5 * (flux_i[k] + flux_j[k]) - 0.5 * (grid.quantities[i][k] - grid.quantities[i - 1][k]) * lambda;

		grid.fluxes[i] = flux_vector;

		if(maxSpeed < lambda)
			maxSpeed = lambda;
	}
}

RiemannSolver::RiemannSolver(Grid& grid, Equations& equations) : grid(grid), equations(equations), maxSpeed(0.) {

}

RiemannSolver::~RiemannSolver() {
	// TODO Auto-generated destructor stub
}

