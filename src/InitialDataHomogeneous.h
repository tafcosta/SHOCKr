/*
 * InitialDataHomogeneous.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATAHOMOGENEOUS_H_
#define SRC_INITIALDATAHOMOGENEOUS_H_

#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"
#include "InitialData.h"

class InitialDataHomogeneous: public InitialData {
public:
	InitialDataHomogeneous(double rhoBackground, double velBackground, double pressureBackground, Grid& grid, EquationsEuler& equations) : InitialData(grid, equations), rhoBackground(rhoBackground), velBackground(velBackground), pressureBackground(pressureBackground){};
	virtual ~InitialDataHomogeneous();
	void setInitialData() override;

	double rhoBackground, velBackground, pressureBackground;

protected:
    void initialize(int i);
};

#endif /* SRC_INITIALDATAHOMOGENEOUS_H_ */
