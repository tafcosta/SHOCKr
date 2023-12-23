/*
 * InitialDataSodShock.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "InitialData.h"
#include "InitialDataSodShock.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"

void InitialDataSodShock::setInitialData(){
	double x;
	double p, rho, u;

		for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){

			x = grid.getX(i);

			if(x < grid.xMidpoint){
				rho = 1;
				p   = 1;
				u   = 0;
			}
			else{
				rho = 0.125;
				p   = 0.1;
				u   = 0;
			}

		grid.quantities[i][EquationsEuler::DENS]   = rho;
		grid.quantities[i][EquationsEuler::XMOM]   = rho * u;
		grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(p, rho * u * u);
		}
}

InitialDataSodShock::~InitialDataSodShock() {
	// TODO Auto-generated destructor stub
}

