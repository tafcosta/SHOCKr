/*
 * InitialDataIsothermal.cpp
 *
 *  Created on: 7 Jan 2024
 *      Author: ntc132
 */

#include "InitialDataIsothermal.h"
#include "InitialData.h"
#include "Equations.h"
#include "EquationsEuler.h"

#include <cmath>

void InitialDataIsothermal::setInitialData() {
	double p, rho, u, rRef;
	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){

		rho  = 0.1;
		p    = 0.01;
		u    = 0.;
		rRef = 1;

		grid.quantities[i][EquationsEuler::DENS]   = rho * std::pow(rRef/grid.getX(i),2.);
		grid.quantities[i][EquationsEuler::XMOM]   = rho * u * std::pow(rRef/grid.getX(i),2.);
		grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(p, rho * u * u * std::pow(rRef/grid.getX(i),2.));
	}
}


InitialDataIsothermal::~InitialDataIsothermal() {
	// TODO Auto-generated destructor stub
}

