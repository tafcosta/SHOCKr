/*
 * RiemannSolverRusanov.cpp
 *
 *  Created on: 20 Jan 2024
 *      Author: ntc132
 */

#include "Equations.h"
#include "Grid.h"
#include "RiemannSolverRusanov.h"

std::vector<double> RiemannSolverRusanov::numericalFlux(std::vector<double>& quantitiesLeft, std::vector<double>& quantitiesRight){
	double lambda = 0.;
	double* flux_i;
	double* flux_j;
	std::vector<double> flux_vector(equations.nCons());

	flux_i = equations.getFlux(quantitiesLeft);
	flux_j = equations.getFlux(quantitiesRight);

	lambda = std::max(equations.getMaxAbsEigenvalue(quantitiesRight), equations.getMaxAbsEigenvalue(quantitiesLeft));

	for(int k = 0; k < equations.nCons(); k++)
		flux_vector[k] = 0.5 * (flux_i[k] + flux_j[k]) - 0.5 * (quantitiesRight[k] - quantitiesLeft[k]) * lambda;

	if(maxSpeed < lambda)
		maxSpeed = lambda;

	return flux_vector;
}

RiemannSolverRusanov::~RiemannSolverRusanov() {
	// TODO Auto-generated destructor stub
}

