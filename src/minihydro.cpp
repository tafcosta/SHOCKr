/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */
#include <iostream>

#include "Boundary.h"
#include "BoundaryWind.h"
#include "BoundaryZeroGradient.h"
#include "BoundaryWindLinearisedEuler.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "EquationsLinearisedEuler.h"
#include "Grid.h"
#include "Grid1D.h"
#include "GridRadial.h"
#include "InitialData.h"
#include "InitialDataHomogeneous.h"
#include "InitialDataHomogeneousLinearisedEuler.h"
#include "InitialDataSodShock.h"
#include "Output.h"
#include "OutputEuler.h"
#include "OutputLinearisedEuler.h"
#include "RiemannSolver.h"

EquationsEuler *equations    = new EquationsEuler(5./3);
Grid *grid                   = new GridRadial(0.1, 1., 1, 1000, *equations);
InitialData *initialdata     = new InitialDataHomogeneous(*grid, *equations);
Boundary *boundary           = new BoundaryWind(*grid, *equations);
Output *output               = new OutputEuler(*grid, *equations);
RiemannSolver *riemannsolver = new RiemannSolver(*grid, *equations);

int main(){
	double CFL = 0.3;
	double maxTime = 0.1;
	double outputTimeInterval = 0.1;
    std::string outputFilename="output.txt";

	double time = 0., dt = 0.;
	double timeSinceLastOutput = 0.0;

	initialdata->setInitialData();

	while(time <= maxTime){

		boundary->setBoundaries();
		riemannsolver->setFluxes();

		if(riemannsolver->maxSpeed > 0)
			dt = CFL * grid->dx / riemannsolver->maxSpeed;
		else
			throw std::runtime_error("Error: Invalid maxSpeed.");

		grid->update(dt);

		if((time == 0.) || (timeSinceLastOutput > outputTimeInterval)){
			output->makeOutput(outputFilename);
			timeSinceLastOutput = 0.;
		}

		std::cout << "time = " << time << std::endl;
		timeSinceLastOutput += dt;
		time += dt;
	}

	output->makeOutput(outputFilename);

	delete boundary;
	delete equations;
	delete grid;
	delete initialdata;
	delete output;
	delete riemannsolver;

	return 0;
}
