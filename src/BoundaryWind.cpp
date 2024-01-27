/*
 * BoundaryWind.cpp
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#include "BoundaryWind.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"

#include <iostream>
#include <cstdio>

void BoundaryWind::setBoundaries(){
	double machNumber = velWind/getSoundSpeed((static_cast<EquationsEuler*>(&equations))->gamma, rhoWind, pressureWind);

	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){
		if (i < grid.minXIndex){

			if (machNumber > 1)
				doSupersonicWind(i);
			else
				doSubsonicWind(i);

		}
		else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

void BoundaryWind::doSupersonicWind(int i){
	grid.quantities[i][EquationsEuler::DENS]   = rhoWind;
	grid.quantities[i][EquationsEuler::XMOM]   = rhoWind * velWind;
	grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureWind, rhoWind * std::pow(velWind, 2.));
}

void BoundaryWind::doSubsonicWind(int i){
	grid.quantities[i][EquationsEuler::DENS]   = rhoWind;
	grid.quantities[i][EquationsEuler::XMOM]   = rhoWind * velWind;

	double rhoOut = rhoBackground;
	double pOut   = pressureBackground;
	double vOut   = velBackground;

	double gamma = (static_cast<EquationsEuler*>(&equations))->gamma;

	double pressureAtBoundary = pOut + ((velWind - vOut)*((1 + gamma) * rhoOut * (velWind - vOut) \
			+ std::sqrt(rhoOut * (16 * gamma * pOut + rhoOut * std::pow(velWind,2) \
			+ gamma * (2 + gamma) * rhoOut * std::pow(velWind,2) \
			- 2 * std::pow(1 + gamma,2) * rhoOut * velWind * vOut + std::pow(1 + gamma, 2) * rhoOut * std::pow(vOut,2))))) / 4.;

	// double pressureAtBoundary = pOut - ((velWind - vOut)*(-((1 + gamma) * rhoOut * (velWind - vOut)) \
			+ std::sqrt(rhoOut * (16* gamma * pOut + rhoOut * std::pow(velWind,2) + gamma*(2 + gamma)*rhoOut*std::pow(velWind,2) \
			- 2*std::pow(1 + gamma,2)*rhoOut*velWind*vOut + std::pow(1 + gamma,2)*rhoOut*std::pow(vOut,2)))))/4.;

	grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureAtBoundary, rhoWind * std::pow(velWind, 2.));
}

double BoundaryWind::getSoundSpeed(double gamma, double density, double pressure){
	if (density == 0)
        throw std::invalid_argument("Wind density cannot be zero.");

	return std::sqrt(gamma * pressure / density);
}

BoundaryWind::~BoundaryWind() {
	// TODO Auto-generated destructor stub
}

