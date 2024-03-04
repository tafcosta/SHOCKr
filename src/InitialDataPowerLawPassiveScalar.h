/*
 * InitialDataPowerLawPassiveScalar.h
 *
 *  Created on: 4 Mar 2024
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATAPOWERLAWPASSIVESCALAR_H_
#define SRC_INITIALDATAPOWERLAWPASSIVESCALAR_H_

#include "Equations.h"
#include "EquationsEulerPassiveScalar.h"
#include "Grid.h"
#include "InitialDataPowerLaw.h"

class InitialDataPowerLawPassiveScalar: public InitialDataPowerLaw {
public:
	InitialDataPowerLawPassiveScalar(double rhoBackground, double velBackground, double pressureBackground, double powerLawExponent, Grid& grid, EquationsEulerPassiveScalar& equations) : InitialDataPowerLaw(rhoBackground, velBackground, pressureBackground, powerLawExponent, grid, equations){};;
	virtual ~InitialDataPowerLawPassiveScalar();

	void setInitialData() override;
};

#endif /* SRC_INITIALDATAPOWERLAWPASSIVESCALAR_H_ */
