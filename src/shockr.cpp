/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */

#include "SimulationDependencies.h"

SimulationConfig config("config.txt");

EquationsEulerPassiveScalar *equations = new EquationsEulerPassiveScalar(5./3);
Grid *grid                             = new GridRadial(config.gridMin, config.gridMax, config.gridNGhost, config.gridNcell, *equations);
Source *source                         = new SourceNone(*grid, *equations); //SourceGravity(*grid, *equations, 1.e7, 6.674e-8 / (std::pow(config.unitLengthInCgs, 3)/config.unitMassInCgs/std::pow(config.unitLengthInCgs/config.unitVelocityInCgs,2)));
InitialData *initialdata               = new InitialDataPowerLawPassiveScalar(config.bgDensity, config.bgVel, config.bgPressure, config.powerLawExponent, *grid, *equations);
Boundary *boundary                     = new BoundaryWindPassiveScalar(config.windDensity, config.windVel, config.windPressure, *grid, *equations);
Output *output                         = new OutputEulerPassiveScalar(*grid, *equations);
RiemannSolver *riemannsolver           = new RiemannSolverHLLC(*grid, *equations);
ShockFinder *shockfinder               = new ShockFinderEuler(*grid, *equations);

void doGreeting();
void freeMemory();

int main(){
	std::string outputFilename = config.outputFile;
	std::string outputEnergy = "energy.txt";

	double CFL = 0.3;
	double maxTime = config.maxTime;
	double outputTimeInterval = config.outputTimeInterval;

	if (std::remove(outputFilename.c_str()) != 0) {}
	if (std::remove(outputEnergy.c_str()) != 0) {}
	double time = 0., dt = 0., timeSinceLastOutput = 0.0;

	doGreeting();

	equations->preProcessor();
	initialdata->setInitialData();


	while(time <= maxTime){

		if((time == 0.) || (timeSinceLastOutput > config.outputTimeInterval)){
			std::cout << "time = " << time << std::endl;
			output->makeOutput(outputFilename, time);
			shockfinder->findShockZones();
			timeSinceLastOutput = 0.;
		}

		boundary->setBoundaries();
		riemannsolver->setFluxes();
		source->setSources();

		if(riemannsolver->maxSpeed > 0)
			dt = CFL * grid->dx / riemannsolver->maxSpeed;
		else
			throw std::runtime_error("Error: Invalid maxSpeed.");

		grid->update(dt);

		timeSinceLastOutput += dt;
		time += dt;
	}

	output->makeOutput(outputFilename, time);
	shockfinder->findShockZones();

	freeMemory();

	std::cout << "All done." << std::endl;
	return 0;
}

void doGreeting(void){
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << " "                                         << std::endl;
    std::cout << "  SSS   H   H   OOO   CCCC  K   K   RRRR " << std::endl;
    std::cout << " S      H   H  O   O  C     K  K    R  R"  << std::endl;
    std::cout << "  SSS   HHHHH  O   O  C     KKK     RRR  " << std::endl;
    std::cout << "     S  H   H  O   O  C     K  K    RR R " << std::endl;
    std::cout << "  SSS   H   H   OOO   CCCC  K   K   R   R" << std::endl;
	std::cout << " "                                         << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "                Version 0                " << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

void freeMemory(void){
	delete boundary;
	delete equations;
	delete grid;
	delete source;
	delete initialdata;
	delete output;
	delete riemannsolver;
	delete shockfinder;
}
