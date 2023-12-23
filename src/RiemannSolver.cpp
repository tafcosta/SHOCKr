/*
 * RiemannSolver.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "Equations.h"
#include "Grid.h"
#include "RiemannSolver.h"

void RiemannSolver::setFluxes(){
	double lambda = 0.;
	double u_i, u_j, cs_i, cs_j;
	double* flux_i;
	double* flux_j;
	std::vector<double> flux_vector(Equations::nCons);

	for(int i = grid.minXIndex; i <= (grid.maxXIndex + 1); i++)
	{
		flux_i = equations.getFlux(grid.quantities[i - 1]);
		flux_j = equations.getFlux(grid.quantities[i]);
		cs_i   = equations.getSoundSpeed(grid.quantities[i - 1]);
		cs_j   = equations.getSoundSpeed(grid.quantities[i]);
		u_i    = grid.quantities[i - 1][Equations::XMOM]/grid.quantities[i - 1][Equations::DENS];
		u_j    = grid.quantities[i][Equations::XMOM]/grid.quantities[i][Equations::DENS];

		lambda = std::max(abs(u_i)+abs(cs_i), abs(u_j)+abs(cs_j));

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

