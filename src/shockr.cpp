/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */

#include "SimulationDependencies.h"

SimulationConfig config("config.txt");

GasProfile* makeGasProfile(const SimulationConfig& c){
	if (c.gasProfile == "homogeneous")
		return new GasProfileHomogeneous(c.bgDensity, c.bgPressure, c.bgVel);
	if (c.gasProfile == "powerlaw")
		return new GasProfilePowerLaw(c.bgDensity, c.bgPressure, c.bgVel, c.powerLawRadius > 0 ? c.powerLawRadius : c.gridMin, c.powerLawExponent);
	if (c.gasProfile == "nfw")
		return new GasProfileNFW(c.haloMass, c.haloConcentration, c.baryonFraction, c.unitLengthInCgs, c.unitMassInCgs, c.unitLengthInCgs/c.unitVelocityInCgs, c.gravity ? c.blackHoleMass : 0.0);
	throw std::runtime_error("Unknown gasProfile: " + c.gasProfile);
}

EquationsEulerPassiveScalar *equations = new EquationsEulerPassiveScalar(5./3);
Grid *grid                             = new GridRadial(config.gridMin, config.gridMax, config.gridNGhost, config.gridNcell, *equations);
GasProfile *gas                        = makeGasProfile(config);
Source *source                         = config.gravity
    ? static_cast<Source*>(new SourceGravity(*grid, *equations, *gas, config.blackHoleMass, 6.674e-8 / (std::pow(config.unitLengthInCgs, 3)/config.unitMassInCgs/std::pow(config.unitLengthInCgs/config.unitVelocityInCgs,2))))
    : static_cast<Source*>(new SourceNone(*grid, *equations));
InitialData *initialdata 			   = new InitialDataRadial(*grid, *equations, *gas);
Boundary *boundary                     = new BoundaryWindPassiveScalar(config.windDensity, config.windVel, config.windPressure, *grid, *equations);
Output *output                         = new OutputEulerPassiveScalar(*grid, *equations);
RiemannSolver *riemannsolver           = new RiemannSolverHLLC(*grid, *equations);
ShockFinder *shockfinder               = new ShockFinderEuler(*grid, *equations);

void doGreeting();
void freeMemory();
std::string removeExtension(const std::string& filename);

int main(){
	double CFL = 0.3;
	double maxTime = config.maxTime;
	double outputTimeInterval = config.outputTimeInterval;

	std::string outputFilename = config.outputFile;
	std::string base = removeExtension(outputFilename);
	std::string outputEnergy   = base + "_energy.txt";
	std::string outputShock    = base + "_shock.txt";

	if (std::remove(outputFilename.c_str()) != 0) {}
	if (std::remove(outputEnergy.c_str()) != 0) {}
	if (std::remove(outputShock.c_str()) != 0) {}

	double time = 0., dt = 0., timeSinceLastOutput = 0.0;

	doGreeting();

	equations->preProcessor();
	initialdata->setInitialData();


	while(time <= maxTime){

		if((time == 0.) || (timeSinceLastOutput > config.outputTimeInterval)){
			std::cout << "time = " << time << std::endl;
			output->makeOutput(outputFilename, outputEnergy, time);
			shockfinder->findShockZones(time, outputShock);
			timeSinceLastOutput = 0.;
		}

		boundary->setBoundaries(time);
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

	std::cout << "time = " << time << std::endl;
	output->makeOutput(outputFilename, outputEnergy, time);
	shockfinder->findShockZones(time, outputShock);

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
	std::cout << "                Version 1                " << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

void freeMemory(void){
	delete boundary;
	delete equations;
	delete gas;
	delete grid;
	delete source;
	delete initialdata;
	delete output;
	delete riemannsolver;
	delete shockfinder;
}

std::string removeExtension(const std::string& filename)
{
    size_t pos = filename.find_last_of('.');

    if (pos == std::string::npos)
        return filename;

    return filename.substr(0, pos);
}
