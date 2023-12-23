/*
 * BoundaryZeroGradient.cpp
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#include "BoundaryZeroGradient.h"
#include "Boundary.h"
#include "Grid.h"

void BoundaryZeroGradient::setBoundaries(){
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++)
	{
		if(i < grid.minXIndex)
			grid.quantities[i] = grid.quantities[grid.minXIndex];
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

BoundaryZeroGradient::~BoundaryZeroGradient() {
	// TODO Auto-generated destructor stub
}

