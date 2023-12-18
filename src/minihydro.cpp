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
double xmin = 0., xmax = 1.;
double dx = 0., xMidpoint, minXIndex, maxXIndex;
std::vector<std::vector<double> > quantities;
std::vector<std::vector<double> > fluxes;

void createGrid(int nx, double dx, double xMidpoint, double minXIndex, double maxXIndex){
	dx = (xmax - xmin)/nx;
	xMidpoint = (xmax + xmin)/2;
	minXIndex = nGhost;
	maxXIndex = nGhost + nx - 1;

	return;
}

double getX(int cellIndex){
	double cellCentre = xmin + (cellIndex - minXIndex) * dx + dx/2.;
	return cellCentre;
}

double totalEnergy(double p, double rhoV2){
	double totalEnergy = p / (gamma - 1) + 0.5 * rhoV2;
	return totalEnergy;
}

double pressure(double e, double rhoV2){
	double p = (gamma - 1) * (e - 0.5 * rhoV2);
	return p;
}

double* getFlux(int cellIndex){
	double* flux = new double[nCons];
	double rhoV2 = quantities[cellIndex][XMOM] * quantities[cellIndex][XMOM] / quantities[cellIndex][DENS];
	double p     = pressure(quantities[cellIndex][ENERGY], rhoV2);

	flux[DENS]   = quantities[cellIndex][XMOM];
	flux[XMOM]   = rhoV2 + p;
	flux[ENERGY] = (p + quantities[cellIndex][ENERGY]) * quantities[cellIndex][XMOM] / quantities[cellIndex][DENS];

	return flux;
}

double getSoundSpeed(int cellIndex){

	double rhoV2 = quantities[cellIndex][XMOM] * quantities[cellIndex][XMOM] / quantities[cellIndex][DENS];
	double p = pressure(quantities[cellIndex][ENERGY], rhoV2);
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

	return;
}

void setInitialData(){
	for(int i = minXIndex; i <= maxXIndex; i++)
		initialDataSodShock(i);

	return;
}

void setBoundaries(){
	for(int i = 0; i < nx + 2*nGhost; i++)
	{
		if(i < minXIndex)
			quantities[i] = quantities[i + nx];
		else if(i > maxXIndex)
			quantities[i] = quantities[i - nx];
	}

	return;
}

void setFluxes(){
	double lambda = 0.;
	double u_i, u_j, cs_i, cs_j;
	double* flux_i;
	double* flux_j;

	for(int i = minXIndex; i == maxXIndex; i++)
	{
		flux_i = getFlux(i);
		flux_j = getFlux(i + 1);
		u_i  = quantities[i][XMOM]/quantities[i][DENS];
		u_j  = quantities[i + 1][XMOM]/quantities[i + 1][DENS];
		cs_i = getSoundSpeed(i);
		cs_j = getSoundSpeed(i + 1);

		lambda = std::max(abs(u_i)+abs(cs_i), abs(u_j)+abs(cs_j));

		fluxes[i] = 0.5 * (quantities[i + 1] - quantities[i]) * lambda;

		if(maxSpeed < lambda)
			maxSpeed = lambda;
	}

	return;
}

void update(double dt){

	for(int i = minXIndex; i == maxXIndex; i++)
		quantities[i]  = quantities[i] - dt/dx * (fluxes[i + 1] - fluxes[i]);

	return;
}

void output(){
	for(int i = minXIndex; i == maxXIndex; i++){
		std::cout << quantities[i][DENS];
	}

	return;
}

int main(){

	double CFL = 0.4;
	double maxTime = 1.0;
	double outputTimeInterval = 0.1;

	double time = 0., dt = 0.;
	double timeSinceLastOutput = 0.0;

	createGrid(nx,dx,xMidpoint, minXIndex, maxXIndex);
	setInitialData();

	while(time <= maxTime){

		setBoundaries();
		setFluxes();

		if(maxSpeed > 0)
			dt = CFL / maxSpeed;
		else
			throw std::runtime_error("Error: maxSpeed must be greater than zero.");

		update(dt);

		if((time == 0.) || (timeSinceLastOutput > outputTimeInterval)){
			output();
			timeSinceLastOutput = 0.;
		}

		timeSinceLastOutput += dt;
		time += dt;
		std::cout << 'time = ' << time << '\n';
	}

	output();

	return 0;
}
