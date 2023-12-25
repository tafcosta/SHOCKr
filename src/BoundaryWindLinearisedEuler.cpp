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
#include "InitialDataHomogeneousLinearisedEuler.h"

void BoundaryWindLinearisedEuler::setBoundaries(){
	double rho_wind, u_wind, p_wind;
	double qminus;
	double cs_background, dens_background;

	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){
		if(i < grid.minXIndex){
			rho_wind = 0.1;
			u_wind   = 0.1;

			cs_background   = (static_cast<EquationsLinearisedEuler*>(&equations))->BgSoundSpeed;
			dens_background = (static_cast<EquationsLinearisedEuler*>(&equations))->BgDensity;
			qminus = (initialdata.p - cs_background * dens_background * initialdata.u) / 2.;
			p_wind = u_wind * dens_background * cs_background + 2 * qminus;

			grid.quantities[i][EquationsLinearisedEuler::DENS]  = rho_wind;
			grid.quantities[i][EquationsLinearisedEuler::VEL]   = u_wind;
			grid.quantities[i][EquationsLinearisedEuler::PRESS] = p_wind;
		}
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

BoundaryWindLinearisedEuler::~BoundaryWindLinearisedEuler() {
	// TODO Auto-generated destructor stub
}

