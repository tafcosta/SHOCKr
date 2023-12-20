/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */
#include <iostream>
#include <fstream>
#include <string>
#include "Grid.h"
#include "Grid1D.h"

// Grid
Grid *grid = new Grid1D(0., 1., 1, 10000);

// Physics
int DENS = 0, XMOM = 1, ENERGY = 2;
double gamma = 1.4;

// Main Loop
double maxSpeed = 0.;

double totalEnergy(double p, double rhoV2){
	double totalEnergy = p / (gamma - 1) + 0.5 * rhoV2;
	return totalEnergy;
}

double getPressure(double e, double rhoV2){
	double p = (gamma - 1) * (e - 0.5 * rhoV2);
	return p;
}

double* getFlux(int cellIndex){
	double* flux = new double[grid->nCons];
	double rhoV2 = grid->quantities[cellIndex][XMOM] * grid->quantities[cellIndex][XMOM] / grid->quantities[cellIndex][DENS];
	double p     = getPressure(grid->quantities[cellIndex][ENERGY], rhoV2);

	flux[DENS]   = grid->quantities[cellIndex][XMOM];
	flux[XMOM]   = rhoV2 + p;
	flux[ENERGY] = (p + grid->quantities[cellIndex][ENERGY]) * grid->quantities[cellIndex][XMOM] / grid->quantities[cellIndex][DENS];

	return flux;
}

double getSoundSpeed(int cellIndex){
	double rhoV2 = grid->quantities[cellIndex][XMOM] * grid->quantities[cellIndex][XMOM] / grid->quantities[cellIndex][DENS];
	double p = getPressure(grid->quantities[cellIndex][ENERGY], rhoV2);
	double rho = grid->quantities[cellIndex][DENS];

	return sqrt(gamma * p / rho);
}

void initialDataSodShock(int i){
	double x = grid->getX(i);
	double p, rho;

	if(x < grid->xMidpoint){
		rho = 1.;
		p = 1;
	}
	else{
		rho = 0.125;
		p = 0.1;
	}

	grid->quantities[i][DENS]   = rho;
	grid->quantities[i][XMOM]   = 0.;
	grid->quantities[i][ENERGY] = totalEnergy(p, 0.);
}

void setInitialData(){
	for(int i = grid->minXIndex; i <= grid->maxXIndex; i++)
		initialDataSodShock(i);
}

void setBoundaries(){
	for(int i = 0; i < grid->nx + 2*grid->nGhost; i++)
	{
		if(i < grid->minXIndex)
			grid->quantities[i] = grid->quantities[grid->minXIndex];
		else if(i > grid->maxXIndex)
			grid->quantities[i] = grid->quantities[grid->maxXIndex];
	}
}

void setFluxes(){
	double lambda = 0.;
	double u_i, u_j, cs_i, cs_j;
	double* flux_i;
	double* flux_j;
	std::vector<double> flux_vector(grid->nCons);

	for(int i = grid->minXIndex; i <= (grid->maxXIndex + 1); i++)
	{
		flux_i = getFlux(i - 1);
		flux_j = getFlux(i);
		cs_i   = getSoundSpeed(i - 1);
		cs_j   = getSoundSpeed(i);
		u_i    = grid->quantities[i - 1][XMOM]/grid->quantities[i - 1][DENS];
		u_j    = grid->quantities[i][XMOM]/grid->quantities[i][DENS];

		lambda = std::max(abs(u_i)+abs(cs_i), abs(u_j)+abs(cs_j));

		for(int k = 0; k < grid->nCons; k++)
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
        outputFile << grid->getX(i) << " " << grid->quantities[i][DENS] << std::endl;
    }

    outputFile.close();
}

int main(){
	double CFL = 0.3;
	double maxTime = 0.1;
	double outputTimeInterval = 0.01;
    std::string outputFilename = "output.txt";

	double time = 0., dt = 0.;
	double timeSinceLastOutput = 0.0;

	setInitialData();

	std::cout << "Begin hydro computation...\n";
	while(time <= maxTime){

		setBoundaries();
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
	delete grid;

	return 0;
}
