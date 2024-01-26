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

	for(int i = 0; i < grid.nx + 2*grid.nGhost; i++){
		if (i < grid.minXIndex){
			if (velWind/getSoundSpeed((static_cast<EquationsEuler*>(&equations))->gamma, rhoWind, pressureWind) > 1)
				doSupersonicWind(i);
			else
				doSubsonicWind(i);
		} else if(i > grid.maxXIndex)
			grid.quantities[i] = grid.quantities[grid.maxXIndex];
	}
}

void BoundaryWind::doSupersonicWind(int i){
	grid.quantities[i][EquationsEuler::DENS]   = rhoWind;
	grid.quantities[i][EquationsEuler::XMOM]   = rhoWind * velWind;
	grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureWind, rhoWind * velWind * velWind);
}

void BoundaryWind::doSubsonicWind(int i){
	double pressureAtBoundary = grid.quantities[grid.minXIndex][EquationsEuler::DENS] * \
			(pressureWind/rhoWind - std::pow(velWind, 2.) * 0.5 * ((static_cast<EquationsEuler*>(&equations))->gamma - 1)/(static_cast<EquationsEuler*>(&equations))->gamma);

	grid.quantities[i][EquationsEuler::DENS]   = grid.quantities[grid.minXIndex][EquationsEuler::DENS];
	grid.quantities[i][EquationsEuler::XMOM]   = grid.quantities[grid.minXIndex][EquationsEuler::DENS] * velWind;
	grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureAtBoundary, grid.quantities[grid.minXIndex][EquationsEuler::DENS] * std::pow(velWind, 2.));
}

double BoundaryWind::getSoundSpeed(double gamma, double density, double pressure){
	if (density == 0)
        throw std::invalid_argument("Wind density cannot be zero.");

	return std::sqrt(gamma * pressure / density);
}

BoundaryWind::~BoundaryWind() {
	// TODO Auto-generated destructor stub
}

