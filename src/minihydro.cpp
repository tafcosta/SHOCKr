/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */
#include <iostream>
#include <fstream>
#include <string>

#include "Boundary.h"
#include "BoundaryWind.h"
#include "BoundaryZeroGradient.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"
#include "Grid1D.h"
#include "GridRadial.h"
#include "InitialData.h"
#include "InitialDataHomogeneous.h"
#include "RiemannSolver.h"

// Grid
EquationsEuler *equations = new EquationsEuler(5./3);
Grid *grid = new GridRadial(0.1, 1., 1, 1000, *equations);
Boundary *boundary = new BoundaryWind(*grid, *equations);
InitialData *initialdata = new InitialDataHomogeneous(*grid, *equations);
RiemannSolver *riemannsolver = new RiemannSolver(*grid, *equations);

void output(const std::string& filename){
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= grid->maxXIndex; i++) {
        outputFile << grid->getX(i) << " " << grid->quantities[i][Equations::DENS] << " " << grid->quantities[i][Equations::XMOM]/grid->quantities[i][Equations::DENS] << std::endl;
    }

    outputFile.close();
}

int main(){
	double CFL = 0.4;
	double maxTime = 0.15;
	double outputTimeInterval = 0.01;
    std::string outputFilename = "output.txt";

	double time = 0., dt = 0.;
	double timeSinceLastOutput = 0.0;

	initialdata->setInitialData();

	while(time <= maxTime){

		//setWindBoundaries();
		boundary->setBoundaries();
		riemannsolver->setFluxes();


		if(riemannsolver->maxSpeed > 0)
			dt = CFL * grid->dx / riemannsolver->maxSpeed;
		else
			throw std::runtime_error("Error: maxSpeed must be greater than zero.");

		grid->update(dt);

		if((time == 0.) || (timeSinceLastOutput > outputTimeInterval)){
			output(outputFilename);
			timeSinceLastOutput = 0.;
		}

		std::cout << "time = " << time << std::endl;
		timeSinceLastOutput += dt;
		time += dt;
	}

	output(outputFilename);

	delete boundary;
	delete equations;
	delete grid;
	delete initialdata;
	delete riemannsolver;

	return 0;
}
