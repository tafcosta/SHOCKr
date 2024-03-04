/*
 * InitialDataIsothermal.h
 *
 *  Created on: 7 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATAPOWERLAW_H_
#define SRC_INITIALDATAPOWERLAW_H_

#include "InitialData.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"

class InitialDataPowerLaw: public InitialData {
public:
	InitialDataPowerLaw(double rhoBackground, double velBackground, double pressureBackground, double powerLawExponent, Grid& grid, EquationsEuler& equations) : InitialData(grid, equations), rhoBackground(rhoBackground), velBackground(velBackground), pressureBackground(pressureBackground), powerLawExponent(powerLawExponent){};

	double rhoBackground, velBackground, pressureBackground, powerLawExponent;

	virtual ~InitialDataPowerLaw();
	void setInitialData() override;
};

#endif /* SRC_INITIALDATAPOWERLAW_H_ */
