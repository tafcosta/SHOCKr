/*
 * minihydro.cpp
 *
 *  Created on: 16 Dec 2023
 *      Author: Tiago Costa
 */

#include "SimulationDependencies.h"

SimulationConfig config("config.txt");

double gravitationalConstantCode(const SimulationConfig& c){
	return 6.674e-8 / (std::pow(c.unitLengthInCgs, 3) / c.unitMassInCgs / std::pow(c.unitLengthInCgs / c.unitVelocityInCgs, 2));
}

GasProfile* makeGasProfile(const SimulationConfig& c){
	if (c.gasProfile == "homogeneous")
		return new GasProfileHomogeneous(c.bgDensity, c.bgPressure, c.bgVel);
	if (c.gasProfile == "powerlaw")
		return new GasProfilePowerLaw(c.bgDensity, c.bgPressure, c.bgVel, c.powerLawRadius > 0 ? c.powerLawRadius : c.gridMin, c.powerLawExponent);
	if (c.gasProfile == "nfw")
   		return new GasProfileNFW(c.haloMass, c.haloConcentration, c.baryonFraction, c.unitLengthInCgs, c.unitMassInCgs, c.unitLengthInCgs/c.unitVelocityInCgs, c.gravity ? c.blackHoleMass : 0.0, c.redshift);
	if (c.gasProfile == "sis")
		return new GasProfileSIS(c.sisSigma, c.gasFraction, gravitationalConstantCode(c), c.gravity ? c.blackHoleMass : 0.0);
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
WindInjection *injection               = new WindInjection(*grid, *equations, config.windDensity, config.windVel, config.windPressure, config.injectionCells);
ArtificialCooling *artificial          = new ArtificialCooling(*grid, *equations, config.artificialCooling, config.windPressure / config.windDensity,
                                                               config.haloPressurePerDensity > 0 ? config.haloPressurePerDensity : config.sisSigma * config.sisSigma);
ComptonCooling *compton                = new ComptonCooling(*grid, *equations, config.comptonCooling, config.agnLuminosity, config.comptonTemperature, config.unitLengthInCgs, config.unitVelocityInCgs, config.comptonRelativistic != 0);

void doGreeting();
void freeMemory();
void writeComptonOutput(const std::string& filename, double time, double windPower);
std::string removeExtension(const std::string& filename);

int main(){
	double CFL = 0.3;
	double maxTime = config.maxTime;
	double outputTimeInterval = config.outputTimeInterval;

	std::string outputFilename = config.outputFile;
	std::string base = removeExtension(outputFilename);
	std::string outputEnergy   = base + "_energy.txt";
	std::string outputShock    = base + "_shock.txt";
	std::string outputCompton  = base + "_compton.txt";

	if (std::remove(outputFilename.c_str()) != 0) {}
	if (std::remove(outputEnergy.c_str()) != 0) {}
	if (std::remove(outputShock.c_str()) != 0) {}
	if (std::remove(outputCompton.c_str()) != 0) {}

	// Wind kinetic power (code units), to express the radiated energy as a fraction
	const double windPower = 2.0 * M_PI * config.gridMin * config.gridMin * config.windDensity * std::pow(config.windVel, 3);

	double time = 0., dt = 0., timeSinceLastOutput = 0.0;

	doGreeting();

	if (config.comptonCooling != 0) {
		if (config.agnLuminosity <= 0.0)
			throw std::runtime_error("comptonCooling needs agnLuminosity > 0");
		std::cout << "Compton cooling mode " << config.comptonCooling << ", L = " << config.agnLuminosity
		          << " erg/s, T_C = " << config.comptonTemperature << " K"
		          << (config.comptonRelativistic ? ", relativistic" : "") << std::endl;
	}

	if (config.outerBoundary == "fixed")
		static_cast<BoundaryWind*>(boundary)->fixedOuterBoundary = true;
	else if (config.outerBoundary != "zerogradient")
		throw std::runtime_error("Unknown outerBoundary: " + config.outerBoundary);
	std::cout << "outer boundary: " << config.outerBoundary << std::endl;

	const bool injectWind = (config.innerBoundary == "injection");
	if (injectWind)
		static_cast<BoundaryWind*>(boundary)->reflectiveInnerBoundary = true;
	else if (config.innerBoundary != "wind")
		throw std::runtime_error("Unknown innerBoundary: " + config.innerBoundary);
	std::cout << "inner boundary: " << config.innerBoundary
	          << (injectWind ? " (wind injected in " + std::to_string(config.injectionCells) + " cells)" : "") << std::endl;

	equations->preProcessor();
	initialdata->setInitialData();


	while(time <= maxTime){

		if((time == 0.) || (timeSinceLastOutput > config.outputTimeInterval)){
			std::cout << "time = " << time << std::endl;
			output->makeOutput(outputFilename, outputEnergy, time);
			shockfinder->findShockZones(time, outputShock);
			writeComptonOutput(outputCompton, time, windPower);
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
		if (injectWind)
			injection->apply(dt);
		compton->apply(dt);
		artificial->apply();

		timeSinceLastOutput += dt;
		time += dt;
	}

	std::cout << "time = " << time << std::endl;
	output->makeOutput(outputFilename, outputEnergy, time);
	shockfinder->findShockZones(time, outputShock);
	writeComptonOutput(outputCompton, time, windPower);

	if (config.artificialCooling != 0)
		std::cout << "Artificial cooling (mode " << config.artificialCooling << "): energy removed = " << artificial->energyRemoved << " (code units)" << std::endl;

	if (config.comptonCooling != 0)
		std::cout << "Compton: net thermal energy radiated = " << compton->energyRadiated << " (code units)" << std::endl;

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
	delete compton;
	delete injection;
	delete artificial;
}

// Time, cumulative thermal energy radiated (code units), and that energy as a
// fraction of the wind kinetic energy injected so far
void writeComptonOutput(const std::string& filename, double time, double windPower){
	if (config.comptonCooling == 0)
		return;
	std::ofstream out(filename, std::ios_base::app);
	out << time << " " << compton->energyRadiated << " "
	    << (time > 0 ? compton->energyRadiated / (windPower * time) : 0.0) << '\n';
}

std::string removeExtension(const std::string& filename)
{
    size_t pos = filename.find_last_of('.');

    if (pos == std::string::npos)
        return filename;

    return filename.substr(0, pos);
}
