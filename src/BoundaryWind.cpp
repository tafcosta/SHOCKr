/*
 * BoundaryWind.cpp
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#include "BoundaryWind.h"
#include "Equations.h"
#include "Grid.h"

void BoundaryWind::setBoundaries(){
	double p, rho, u;

	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){
		if(i < grid.minXIndex){
			rho = 1.;
			p   = 5.;
			u   = 5.;

			grid.quantities[i][Equations::DENS]   = rho;
			grid.quantities[i][Equations::XMOM]   = rho * u;
			grid.quantities[i][Equations::ENERGY] = equations.totalEnergy(p, rho * u * u);
		}
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

BoundaryWind::~BoundaryWind() {
	// TODO Auto-generated destructor stub
}

