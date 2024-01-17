/*
 * ShockFinderEulerPassiveScalar.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: ntc132
 */

#include "ShockFinderEulerPassiveScalar.h"
#include "EquationsEulerPassiveScalar.h"

void ShockFinderEulerPassiveScalar::findShockZones(void){

	double rho, p, T, u, rhoV2;
    for (int i = 0; i <= grid.maxXIndex; i++) {
    	rho   = grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	rhoV2 = pow(grid.quantities[i][EquationsEulerPassiveScalar::XMOM], 2.) / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	p     = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2);
    	T     = p/rho;
    	u     = grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    }

return;
}

void ShockFinderEulerPassiveScalar::findShockDirection(void){

	double rho, p, T, u, rhoV2;
    for (int i = 0; i <= grid.maxXIndex; i++) {
    	rho   = grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	rhoV2 = pow(grid.quantities[i][EquationsEulerPassiveScalar::XMOM], 2.) / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	p     = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2);
    	T     = p/rho;
    	u     = grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    }

return;
}

void ShockFinderEulerPassiveScalar::calculateGradients(void){

	double rho, p, T, u, rhoV2;
    for (int i = grid.minXIndex; i <= grid.maxXIndex; i++) {

    	rho   = grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	rhoV2 = pow(grid.quantities[i][EquationsEulerPassiveScalar::XMOM], 2.) / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    	p     = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2);
    	T     = p/rho;
    	u     = grid.quantities[i][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i][EquationsEulerPassiveScalar::DENS];




    }

return;
}


ShockFinderEulerPassiveScalar::~ShockFinderEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

