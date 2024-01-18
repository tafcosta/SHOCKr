/*
 * ShockFinderEulerPassiveScalar.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: ntc132
 */

#include <iostream>

#include "ShockFinder.h"
#include "ShockFinderEulerPassiveScalar.h"
#include "EquationsEulerPassiveScalar.h"

std::vector<int> ShockFinderEulerPassiveScalar::findShockZones(void){
	this->gradients = std::vector<std::vector<double> > (grid.nx + 2*grid.nGhost, std::vector<double>(2, 0.0));
	this->divV      = std::vector<double>(grid.nx + 2*grid.nGhost, 0.0);
	this->shock     = std::vector<int>(grid.nx + 2*grid.nGhost, 0);

    for (int i = grid.minXIndex; i <= grid.maxXIndex; i++){

    	calculateGradients(i);
    	calculateDivV(i);
    	detectShockZone(i, divV[i], gradients[i][DENS], gradients[i][TEMP]);

    	std::cout << shock[i] << std::endl;
    }

    return shock;
}

void ShockFinderEulerPassiveScalar::detectShockZone(int i, double divV_i, double gradientDens_i, double gradientTemp_i) {
	if (divV_i < 0 && (gradientTemp_i * gradientDens_i > 0))
		shock[i] = 1;
}

void ShockFinderEulerPassiveScalar::calculateGradients(int i) {
	double rho_i, rho_j, p_i, p_j, rhoV2_i, rhoV2_j, T_i, T_j;

	rho_i   = grid.quantities[i][EquationsEulerPassiveScalar::DENS];
	rho_j   = grid.quantities[i + 1][EquationsEulerPassiveScalar::DENS];

	rhoV2_i = pow(grid.quantities[i][EquationsEulerPassiveScalar::XMOM], 2.) / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
	rhoV2_j = pow(grid.quantities[i + 1][EquationsEulerPassiveScalar::XMOM], 2.) / grid.quantities[i + 1][EquationsEulerPassiveScalar::DENS];
	p_i     = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2_i);
	p_j     = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i + 1][EquationsEulerPassiveScalar::ENERGY], rhoV2_j);

	T_i     = p_i/rho_i;
	T_j     = p_j/rho_j;

	gradients[i][DENS] = (rho_j - rho_i) / (grid.getX(i + 1) - grid.getX(i));
	gradients[i][TEMP] = (T_j - T_i)     / (grid.getX(i + 1) - grid.getX(i));
}


void ShockFinderEulerPassiveScalar::calculateDivV(int i) {
	double u_i, u_j;

    u_i     = grid.quantities[i][EquationsEulerPassiveScalar::XMOM]     / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    u_j     = grid.quantities[i + 1][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i + 1][EquationsEulerPassiveScalar::DENS];

	divV[i] = (u_j * pow(grid.getX(i + 1), 2.) - u_i * pow(grid.getX(i), 2.)) / (grid.getX(i + 1) - grid.getX(i)) / pow(grid.getX(i), 2.);
}

ShockFinderEulerPassiveScalar::~ShockFinderEulerPassiveScalar() {
	// TODO Auto-generated destructor stub
}

