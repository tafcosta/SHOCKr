/*
 * BoundaryWindLinearisedEuler.cpp
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "BoundaryWindLinearisedEuler.h"
#include "Equations.h"
#include "EquationsLinearisedEuler.h"
#include "Grid.h"

void BoundaryWindLinearisedEuler::setBoundaries(){
	double rho, u, p;
	double q0, qplus, qminus;
	double cs_background, dens_background;

	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){
		if(i < grid.minXIndex){
			rho = 0.1;
			u   = 0.3;
			p   = 1.;



			cs_background   = (static_cast<EquationsLinearisedEuler*>(&equations))->BgSoundSpeed;
			dens_background = (static_cast<EquationsLinearisedEuler*>(&equations))->BgDensity;

			q0     = rho - p / pow(cs_background, 2.);
			qplus  = (p + cs_background * dens_background * u) / 2.;
			qminus = (grid.quantities[grid.minXIndex][EquationsLinearisedEuler::PRESS] - cs_background * dens_background * grid.quantities[grid.minXIndex][EquationsLinearisedEuler::VEL]) / 2.;

			grid.quantities[i][EquationsLinearisedEuler::DENS]  = q0 + (qplus + qminus) / pow(cs_background, 2.);
			grid.quantities[i][EquationsLinearisedEuler::VEL]   = (qplus - qminus) / (cs_background * dens_background);
			grid.quantities[i][EquationsLinearisedEuler::PRESS] = qplus + qminus;
		}
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

BoundaryWindLinearisedEuler::~BoundaryWindLinearisedEuler() {
	// TODO Auto-generated destructor stub
}

