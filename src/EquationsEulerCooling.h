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

	static const double temperatureRef = 0.1;

	std::vector<std::vector<double> > coolingTable;

	double coolingRate(double temperature);
	void   doCooling(std::vector<double>& quantities, double dt);

	double getCoolingTime(double temperature);
	double getInverseTemporalEvolutionFunction(double Y);
	double getTemporalEvolutionFunction(double temperature);
	double getTemperatureInternalUnits(std::vector<double>& quantities);

	void   preProcessor() override;
	void   postProcessor(std::vector<double>& quantities, double dt) override;


};

#endif /* SRC_EQUATIONSEULERCOOLING_H_ */
