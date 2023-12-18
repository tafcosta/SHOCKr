/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */
#include <iostream>

// Physics
int DENS = 0, XMOM = 1, ENERGY = 2;
double gamma = 5./3;

// Main Loop
double maxSpeed = 0.;

// Grid
int nx = 100, nGhost = 1, nCons = 3;
double xmin = 0., xmax = 1., dx = 0.;
double xMidpoint = 0.;
int minXIndex = 0, maxXIndex = 0;

std::vector<std::vector<double> > quantities(nx + 2*nGhost, std::vector<double>(nCons, 0.0));
std::vector<std::vector<double> > fluxes(nx + 2*nGhost + 1, std::vector<double>(nCons, 0.0));

void createGrid(int nx, double &dx, double &xMidpoint, int &minXIndex, int &maxXIndex){
	dx = (xmax - xmin)/nx;
	xMidpoint = (xmax + xmin)/2;
	minXIndex = nGhost;
	maxXIndex = nGhost + nx - 1;
}

double getX(int cellIndex){
	double cellCentre = xmin + (cellIndex - minXIndex) * dx + dx/2.;
	return cellCentre;
}

double totalEnergy(double p, double rhoV2){
	double totalEnergy = p / (gamma - 1) + 0.5 * rhoV2;
	return totalEnergy;
}

double getPressure(double e, double rhoV2){
	double p = (gamma - 1) * (e - 0.5 * rhoV2);
	return p;
}

double* getFlux(int cellIndex){
	double* flux = new double[nCons];
	double rhoV2 = quantities[cellIndex][XMOM] * quantities[cellIndex][XMOM] / quantities[cellIndex][DENS];
	double p     = getPressure(quantities[cellIndex][ENERGY], rhoV2);

	flux[DENS]   = quantities[cellIndex][XMOM];
	flux[XMOM]   = rhoV2 + p;
	flux[ENERGY] = (p + quantities[cellIndex][ENERGY]) * quantities[cellIndex][XMOM] / quantities[cellIndex][DENS];

	return flux;
}

double getSoundSpeed(int cellIndex){
	double rhoV2 = quantities[cellIndex][XMOM] * quantities[cellIndex][XMOM] / quantities[cellIndex][DENS];
	double p = getPressure(quantities[cellIndex][ENERGY], rhoV2);
	double rho = quantities[cellIndex][DENS];

	return sqrt(gamma * p / rho);
}

void initialDataSodShock(int i){
	double x = getX(i);
	double p, rho;

	if(x < xMidpoint){
		rho = 1.;
		p = 1;
	}
	else{
		rho = 0.125;
		p = 0.1;
	}

	quantities[i][DENS]   = rho;
	quantities[i][XMOM]   = 0.;
	quantities[i][ENERGY] = totalEnergy(p, 0.);
}

void setInitialData(){
	for(int i = minXIndex; i <= maxXIndex; i++)
		initialDataSodShock(i);
}

void setBoundaries(){
	for(int i = 0; i < nx + 2*nGhost; i++)
	{
		if(i < minXIndex)
			quantities[i] = quantities[i + nx];
		else if(i > maxXIndex)
			quantities[i] = quantities[i - nx];
	}
}

void setFluxes(){
	double lambda = 0.;
	double u_i, u_j, cs_i, cs_j;
	double* flux_i;
	double* flux_j;
	std::vector<double> flux_vector(nCons);

	for(int i = minXIndex; i <= maxXIndex; i++)
	{
		flux_i = getFlux(i);
		flux_j = getFlux(i + 1);
		cs_i   = getSoundSpeed(i);
		cs_j   = getSoundSpeed(i + 1);
		u_i    = quantities[i][XMOM]/quantities[i][DENS];
		u_j    = quantities[i + 1][XMOM]/quantities[i + 1][DENS];

		lambda = std::max(abs(u_i)+abs(cs_i), abs(u_j)+abs(cs_j));

		for(int k = 0; k < nCons; k++)
			flux_vector[k] = 0.5 * (flux_i[k] + flux_j[k]) - 0.5 * (quantities[i + 1][k] - quantities[i][k]) * lambda;

		fluxes[i] = flux_vector;

		if(maxSpeed < lambda)
			maxSpeed = lambda;
	}
}

void update(double dt){
	for(int i = minXIndex; i <= maxXIndex; i++)
		for(int k = 0; k < nCons; k++)
			quantities[i][k]  = quantities[i][k] - dt/dx * (fluxes[i + 1][k] - fluxes[i][k]);

}

void output(){
	for(int i = minXIndex; i <= maxXIndex; i++)
		std::cout << quantities[i][DENS] << ", ";
}

int main(){
	double CFL = 0.4;
	double maxTime = 0.01;
	double outputTimeInterval = 0.1;

	double time = 0., dt = 0.;
	double timeSinceLastOutput = 0.0;

	createGrid(nx,dx,xMidpoint,minXIndex,maxXIndex);
	setInitialData();

	std::cout << "Begin hydro computation...\n";

	while(time <= maxTime){

		setBoundaries();
		setFluxes();

		if(maxSpeed > 0)
			dt = CFL * dx / maxSpeed;
		else
			throw std::runtime_error("Error: maxSpeed must be greater than zero.");

		update(dt);
		output();

		if((time == 0.) || (timeSinceLastOutput > outputTimeInterval)){
			output();
			timeSinceLastOutput = 0.;
		}

		std::cout << "time = " << time << std::endl;
		timeSinceLastOutput += dt;
		time += dt;
	}

	output();
	return 0;
}
