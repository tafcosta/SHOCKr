/*
 * InitialDataHomogeneous.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "InitialData.h"
#include "InitialDataHomogeneous.h"
#include "Equations.h"
#include "Grid.h"

void InitialDataHomogeneous::setInitialData() {
	double p, rho, u;
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){

		rho = 1.;
		p   = 1.;
		u   = 0.;

		grid.quantities[i][Equations::DENS]   = rho;
		grid.quantities[i][Equations::XMOM]   = rho * u;
		grid.quantities[i][Equations::ENERGY] = equations.totalEnergy(p, rho * u * u);
	}
}

InitialDataHomogeneous::~InitialDataHomogeneous() {
	// TODO Auto-generated destructor stub
}

