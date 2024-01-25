/*
 * BoundaryWind.cpp
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#include "BoundaryWind.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"

void BoundaryWind::setBoundaries(){
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){
		if(i < grid.minXIndex){
			grid.quantities[i][EquationsEuler::DENS]   = rhoWind;
			grid.quantities[i][EquationsEuler::XMOM]   = rhoWind * velWind;
			grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureWind, rhoWind * velWind * velWind);
		}
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

BoundaryWind::~BoundaryWind() {
	// TODO Auto-generated destructor stub
}

