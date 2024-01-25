/*
 * BoundaryWindPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "BoundaryWindPassiveScalar.h"
#include "EquationsEulerPassiveScalar.h"
#include "Grid.h"

void BoundaryWindPassiveScalar::setBoundaries(){
	double p, rho, rhoPassiveScalar, u;

	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){
		if(i < grid.minXIndex){
			grid.quantities[i][EquationsEuler::DENS]   = rhoWind;
			grid.quantities[i][EquationsEuler::XMOM]   = rhoWind * velWind;
			grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureWind, rhoWind * velWind * velWind);
			grid.quantities[i][EquationsEulerPassiveScalar::PASS]   = rhoWind;
		}
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

BoundaryWindPassiveScalar::~BoundaryWindPassiveScalar() {
	// TODO Auto-generated destructor stub
}

