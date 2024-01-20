
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

void RiemannSolver::setFluxes(void){
	for(int i = grid.minXIndex; i <= (grid.maxXIndex + 1); i++)
		grid.fluxes[i] = numericalFlux(grid.quantities[i - 1], grid.quantities[i]);
}

RiemannSolver::RiemannSolver(Grid& grid, Equations& equations) : grid(grid), equations(equations), maxSpeed(0.) {

}

RiemannSolver::~RiemannSolver() {
	// TODO Auto-generated destructor stub
}
