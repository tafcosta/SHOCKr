/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */
#include <iostream>
#include <cstdio>

#include "Boundary.h"
#include "BoundaryWind.h"
#include "BoundaryZeroGradient.h"
#include "BoundaryWindLinearisedEuler.h"
#include "BoundaryWindPassiveScalar.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "EquationsEulerPassiveScalar.h"
#include "EquationsLinearisedEuler.h"
#include "Grid.h"
#include "Grid1D.h"
#include "GridRadial.h"
#include "InitialData.h"
#include "InitialDataHomogeneous.h"
#include "InitialDataHomogeneousLinearisedEuler.h"
#include "InitialDataHomogeneousPassiveScalar.h"
#include "InitialDataIsothermal.h"
#include "InitialDataSodShock.h"
#include "Output.h"
#include "OutputEuler.h"
#include "OutputEulerPassiveScalar.h"
#include "OutputLinearisedEuler.h"
#include "RiemannSolver.h"
#include "RiemannSolverHLLC.h"
#include "RiemannSolverRusanov.h"
#include "ShockFinder.h"
#include "ShockFinderEulerPassiveScalar.h"

EquationsEulerPassiveScalar *equations = new EquationsEulerPassiveScalar(5./3);
Grid *grid                   = new GridRadial(0.01, 10., 1, 1000, *equations);
InitialData *initialdata     = new InitialDataHomogeneousPassiveScalar(*grid, *equations);
Boundary *boundary           = new BoundaryWindPassiveScalar(*grid, *equations);
Output *output               = new OutputEulerPassiveScalar(*grid, *equations);
RiemannSolver *riemannsolver = new RiemannSolverHLLC(*grid, *equations);
ShockFinder *shockfinder     = new ShockFinderEulerPassiveScalar(*grid, *equations);

void freeMemory(void){
	delete boundary;
	delete equations;
	delete grid;
	delete initialdata;
	delete output;
	delete riemannsolver;
	delete shockfinder;
}

int main(){
	double CFL = 0.3;
	double maxTime = 0.5;
	double outputTimeInterval = 0.01;
    std::string outputFilename="output_hllc.txt";
    std::string outputEnergy="energy.txt";

	double time = 0., dt = 0.;
	double timeSinceLastOutput = 0.0;

	if (std::remove(outputFilename.c_str()) != 0) {}
	if (std::remove(outputEnergy.c_str()) != 0) {}

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
			shockfinder->findShockZones();
			timeSinceLastOutput = 0.;
		}

		std::cout << "time = " << time << std::endl;
		timeSinceLastOutput += dt;
		time += dt;
	}

	output->makeOutput(outputFilename);
	shockfinder->findShockZones();

	freeMemory();
	return 0;
}
