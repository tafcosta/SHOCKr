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

	BoundaryWind::setBoundaries();

	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++)
		if(i < grid.minXIndex)
			grid.quantities[i][EquationsEulerPassiveScalar::PASS]   = rhoWind;
}

BoundaryWindPassiveScalar::~BoundaryWindPassiveScalar() {
	// TODO Auto-generated destructor stub
}

