/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */

#include "SimulationDependencies.h"

SimulationConfig config("config.txt");

EquationsEulerPassiveScalar *equations = new EquationsEulerPassiveScalar(config.gamma);
Grid *grid                   = new GridRadial(config.gridMin, config.gridMax, config.gridNGhost, config.gridNcell, *equations);
InitialData *initialdata     = new InitialDataHomogeneousPassiveScalar(*grid, *equations);
Boundary *boundary           = new BoundaryWindPassiveScalar(*grid, *equations);
Output *output               = new OutputEulerPassiveScalar(*grid, *equations);
RiemannSolver *riemannsolver = new RiemannSolverHLLC(*grid, *equations);
ShockFinder *shockfinder     = new ShockFinderEulerPassiveScalar(*grid, *equations);

void doGreeting();
void freeMemory();

int main(){
	std::string outputFilename = config.outputFilename;
	std::string outputEnergy   = config.outputEnergy;

	if (std::remove(outputFilename.c_str()) != 0) {}
	if (std::remove(outputEnergy.c_str()) != 0) {}

	double time = 0., dt = 0., timeSinceLastOutput = 0.0;

	doGreeting();
	initialdata->setInitialData();

	while(time <= config.maxTime){

		boundary->setBoundaries();
		riemannsolver->setFluxes();

		if(riemannsolver->maxSpeed > 0)
			dt = config.CFL * grid->dx / riemannsolver->maxSpeed;
		else
			throw std::runtime_error("Error: Invalid maxSpeed.");

		grid->update(dt);

		if((time == 0.) || (timeSinceLastOutput > config.outputTimeInterval)){
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
	std::cout << "All done." << std::endl;
	return 0;
}

void doGreeting(void){
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << " " << std::endl;
    std::cout << "  SSS   H   H   OOO   CCCC  K   K   RRRR " << std::endl;
    std::cout << " S      H   H  O   O  C     K  K    R  R"  << std::endl;
    std::cout << "  SSS   HHHHH  O   O  C     KKK     RRR  " << std::endl;
    std::cout << "     S  H   H  O   O  C     K  K    RR R " << std::endl;
    std::cout << "  SSS   H   H   OOO   CCCC  K   K   R   R" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "                Version 0                " << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

void freeMemory(void){
	delete boundary;
	delete equations;
	delete grid;
	delete initialdata;
	delete output;
	delete riemannsolver;
	delete shockfinder;
}
