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
#include "Grid.h"
#include "Grid1D.h"
#include "GridRadial.h"
#include "InitialData.h"
#include "InitialDataHomogeneous.h"

// Grid
Equations *equations = new Equations(5./3);
Grid *grid = new GridRadial(0.1, 1., 1, 10000, *equations);
Boundary *boundary = new BoundaryWind(*grid, *equations);
InitialData *initialdata = new InitialDataHomogeneous(*grid, *equations);

// Main Loop
double maxSpeed = 0.;

void setFluxes(){
	double lambda = 0.;
	double u_i, u_j, cs_i, cs_j;
	double* flux_i;
	double* flux_j;
	std::vector<double> flux_vector(Equations::nCons);

	for(int i = grid->minXIndex; i <= (grid->maxXIndex + 1); i++)
	{
		flux_i = equations->getFlux(grid->quantities[i - 1]);
		flux_j = equations->getFlux(grid->quantities[i]);
		cs_i   = equations->getSoundSpeed(grid->quantities[i - 1]);
		cs_j   = equations->getSoundSpeed(grid->quantities[i]);
		u_i    = grid->quantities[i - 1][Equations::XMOM]/grid->quantities[i - 1][Equations::DENS];
		u_j    = grid->quantities[i][Equations::XMOM]/grid->quantities[i][Equations::DENS];

		lambda = std::max(abs(u_i)+abs(cs_i), abs(u_j)+abs(cs_j));

		for(int k = 0; k < Equations::nCons; k++)
			flux_vector[k] = 0.5 * (flux_i[k] + flux_j[k]) - 0.5 * (grid->quantities[i][k] - grid->quantities[i - 1][k]) * lambda;

		grid->fluxes[i] = flux_vector;

		if(maxSpeed < lambda)
			maxSpeed = lambda;
	}
}

void output(const std::string& filename){
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = grid->minXIndex; i <= grid->maxXIndex; i++) {
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

	std::cout << "Begin hydro computation...\n";
	while(time <= maxTime){

		//setWindBoundaries();
		boundary->setBoundaries();
		setFluxes();

		if(maxSpeed > 0)
			dt = CFL * grid->dx / maxSpeed;
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


	return 0;
}
