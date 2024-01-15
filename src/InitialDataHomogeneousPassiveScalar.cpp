/*
 * InitialDataHomogeneousPassiveScalar.cpp
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#include "InitialDataHomogeneousPassiveScalar.h"
#include "InitialData.h"
#include "Equations.h"
#include "EquationsEulerPassiveScalar.h"

void InitialDataHomogeneousPassiveScalar::setInitialData() {
	double p, rho, u;
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){

		rho = 0.1;
		p   = 0.01;
		u   = 0.;

		grid.quantities[i][EquationsEulerPassiveScalar::DENS]   = rho;
		grid.quantities[i][EquationsEulerPassiveScalar::XMOM]   = rho * u;
		grid.quantities[i][EquationsEulerPassiveScalar::ENERGY] = (static_cast<EquationsEulerPassiveScalar*>(&equations))->totalEnergy(p, rho * u * u);
		grid.quantities[i][EquationsEulerPassiveScalar::PASS]   = 0.0001;
	}
}

InitialDataHomogeneousPassiveScalar::~InitialDataHomogeneousPassiveScalar() {
	// TODO Auto-generated destructor stub
}

