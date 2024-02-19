/*
 * EquationsEulerCooling.h
 *
 *  Created on: 13 Feb 2024
 *      Author: ntc132
 */

#ifndef SRC_EQUATIONSEULERCOOLING_H_
#define SRC_EQUATIONSEULERCOOLING_H_

#include "EquationsEuler.h"
#include "Grid.h"
#include "SimulationConfig.h"

class EquationsEulerCooling: public EquationsEuler {
public:
	EquationsEulerCooling(double gamma, double unitL, double unitM, double unitV) : EquationsEuler(gamma), unitL(unitL), unitM(unitM), unitV(unitV) {};
	virtual ~EquationsEulerCooling();

protected:

	double unitL, unitM, unitV;
	double const BOLTZMANN_CONSTANT = 1.3807e-16;
	double const PROTON_MASS = 1.66e-24;

	double coolingRateRef, temperatureRef;
	int numTemperatureEdges;

    std::vector<double> temperatureBins;
    std::vector<double> coolingRateEdgeBin;
    std::vector<double> slope;
	std::vector<std::vector<double> > coolingTable;

	double coolingRate(double temperature);
	void   doCooling(std::vector<double>& quantities, double dt);

	double getCoolingTime(double temperature);
	double getInverseTemporalEvolutionFunction(double temperature, double TemporalEvolutionFunction);
	double getTemporalEvolutionFunction(double temperature);
	double getTemperaturePhysicalUnits(std::vector<double>& quantities);

	void   preProcessor() override;
	void   postProcessor(std::vector<double>& quantities, double dt) override;


};

#endif /* SRC_EQUATIONSEULERCOOLING_H_ */
