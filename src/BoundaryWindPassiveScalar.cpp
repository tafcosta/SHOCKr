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
			rho = 1000.;
			rhoPassiveScalar = 1000.;
			p   = 0.0001;
			u   = 20.;

			grid.quantities[i][EquationsEulerPassiveScalar::DENS]   = rho;
			grid.quantities[i][EquationsEulerPassiveScalar::XMOM]   = rho * u;
			grid.quantities[i][EquationsEulerPassiveScalar::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(p, rho * u * u);
			grid.quantities[i][EquationsEulerPassiveScalar::PASS]   = rhoPassiveScalar;
		}
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

BoundaryWindPassiveScalar::~BoundaryWindPassiveScalar() {
	// TODO Auto-generated destructor stub
}

