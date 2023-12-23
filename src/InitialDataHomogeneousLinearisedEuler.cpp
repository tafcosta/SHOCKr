/*
 * InitialDataHomogeneousLinearisedEuler.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "InitialDataHomogeneousLinearisedEuler.h"
#include "InitialData.h"
#include "Equations.h"
#include "Grid.h"

void InitialDataHomogeneousLinearisedEuler::setInitialData() {
	double rho, u, p;
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){

		rho = 1;
		u   = 0.;
		p   = 1.;

		grid.quantities[i][EquationsLinearisedEuler::DENS]  = rho;
		grid.quantities[i][EquationsLinearisedEuler::VEL]   = u;
		grid.quantities[i][EquationsLinearisedEuler::PRESS] = p;
	}
}

InitialDataHomogeneousLinearisedEuler::~InitialDataHomogeneousLinearisedEuler() {
	// TODO Auto-generated destructor stub
}

