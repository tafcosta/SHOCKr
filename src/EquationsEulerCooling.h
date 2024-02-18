/*
 * EquationsEulerCooling.h
 *
 *  Created on: 13 Feb 2024
 *      Author: ntc132
 */

#ifndef SRC_EQUATIONSEULERCOOLING_H_
#define SRC_EQUATIONSEULERCOOLING_H_

#include "EquationsEuler.h"

class EquationsEulerCooling: public EquationsEuler {
public:
	EquationsEulerCooling(double gamma) : EquationsEuler(gamma) {};
	virtual ~EquationsEulerCooling();

protected:

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
	double getTemperatureInternalUnits(std::vector<double>& quantities);

	void   preProcessor() override;
	void   postProcessor(std::vector<double>& quantities, double dt) override;


};

#endif /* SRC_EQUATIONSEULERCOOLING_H_ */
