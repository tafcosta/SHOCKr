/*
 * InitialDataHomogeneous.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "InitialData.h"
#include "InitialDataHomogeneous.h"
#include "Equations.h"
#include "EquationsEuler.h"

void InitialDataHomogeneous::setInitialData() {
    for(int i = 0; i < grid.nx + 2*grid.nGhost; i++)
        initialize(i);
}

void InitialDataHomogeneous::initialize(int i) {

    grid.quantities[i][EquationsEuler::DENS]   = rhoBackground;
    grid.quantities[i][EquationsEuler::XMOM]   = rhoBackground * velBackground;
    grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureBackground, rhoBackground * velBackground * velBackground);
}

InitialDataHomogeneous::~InitialDataHomogeneous() {
	// TODO Auto-generated destructor stub
}

