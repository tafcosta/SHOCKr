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
	double p, rho, u;
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){

		rho = 0.1;
		p   = 0.01;
		u   = 0.;

		grid.quantities[i][EquationsEuler::DENS]   = rho;
		grid.quantities[i][EquationsEuler::XMOM]   = rho * u;
		grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(p, rho * u * u);
	}
}

InitialDataHomogeneous::~InitialDataHomogeneous() {
	// TODO Auto-generated destructor stub
}

