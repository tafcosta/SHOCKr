/*
 * InitialDataIsothermal.cpp
 *
 *  Created on: 7 Jan 2024
 *      Author: ntc132
 */

#include "InitialDataPowerLaw.h"

#include "InitialData.h"
#include "Equations.h"
#include "EquationsEuler.h"

#include <cmath>

void InitialDataPowerLaw::setInitialData() {
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){

		grid.quantities[i][EquationsEuler::DENS]   = rhoBackground * std::pow(grid.xmin/grid.getX(i),powerLawExponent);
		grid.quantities[i][EquationsEuler::XMOM]   = rhoBackground * velBackground * std::pow(grid.xmin/grid.getX(i),powerLawExponent);
		grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureBackground, rhoBackground * velBackground * velBackground * std::pow(grid.xmin/grid.getX(i),powerLawExponent));
	}
}


InitialDataPowerLaw::~InitialDataPowerLaw() {
	// TODO Auto-generated destructor stub
}

