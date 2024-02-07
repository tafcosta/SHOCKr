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

	for(int i = 0; i < grid.nx + 2 * grid.nGhost; i++){
		if (i < grid.minXIndex){

			if (machNumber > 1)
				doSupersonicWind(i);
			else
				doSubsonicWindGross(i);

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

	double gamma = (static_cast<EquationsEuler*>(&equations))->gamma;
	double pressureAtBoundary = pressureBackground + ((velWind - velBackground)*((1 + gamma) * rhoBackground * (velWind - velBackground) \
			+ std::sqrt(rhoBackground * (16 * gamma * pressureBackground + rhoBackground * std::pow(velWind,2) \
			+ gamma * (2 + gamma) * rhoBackground * std::pow(velWind,2) \
			- 2 * std::pow(1 + gamma,2) * rhoBackground * velWind * velBackground + std::pow(1 + gamma, 2) * rhoBackground * std::pow(velBackground,2))))) / 4.;

	grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pressureAtBoundary, rhoBackground * std::pow(velWind, 2.));
}


void BoundaryWind::doSubsonicWindGross(int i){
	double rho, rho_j, rho_k, vx, vel_j, vel_k, p, p_j, p_k;
	double rhoGhost, velGhost, pGhost;
	double soundSpeed;

	std::vector<double> charDerivatives (3, 0.0), charDerivativesWind (3, 0.0), charDerivativesMixed (3, 0.0);
	std::vector<double> primitiveDerivatives (3, 0.0), primitiveDerivativesWind (3, 0.0), primitiveDerivativesMixed (3, 0.0);

	double gamma = (static_cast<EquationsEuler*>(&equations))->gamma;

	rho   = grid.quantities[grid.minXIndex][EquationsEuler::DENS];
	rho_j = grid.quantities[grid.minXIndex + 1][EquationsEuler::DENS];
	rho_k = grid.quantities[grid.minXIndex + 2][EquationsEuler::DENS];

	vx    = grid.quantities[grid.minXIndex][EquationsEuler::XMOM]/grid.quantities[grid.minXIndex][EquationsEuler::DENS];
	vel_j = grid.quantities[grid.minXIndex + 1][EquationsEuler::XMOM]/grid.quantities[grid.minXIndex + 1][EquationsEuler::DENS];
	vel_k = grid.quantities[grid.minXIndex + 2][EquationsEuler::XMOM]/grid.quantities[grid.minXIndex + 2][EquationsEuler::DENS];

	p     = (static_cast<EquationsEuler*>(&equations))->getPressure(grid.quantities[grid.minXIndex][EquationsEuler::ENERGY],       rho * std::pow(vx, 2.));
	p_j   = (static_cast<EquationsEuler*>(&equations))->getPressure(grid.quantities[grid.minXIndex + 1][EquationsEuler::ENERGY], rho_j * std::pow(vel_j, 2.));
	p_k   = (static_cast<EquationsEuler*>(&equations))->getPressure(grid.quantities[grid.minXIndex + 2][EquationsEuler::ENERGY], rho_k * std::pow(vel_k, 2.));

	soundSpeed = std::sqrt(gamma * p/rho);

	primitiveDerivatives[0]     = (-rho_k + 3 * rho_j -2 * rho)/grid.dx; //(rho_j - rho) /grid.dx;
	primitiveDerivatives[1]     = (-vel_k + 3 * vel_j -2 * vx) /grid.dx; //(vel_j - vx)  /grid.dx;
	primitiveDerivatives[2]     = (-p_k   + 3 * p_j   -2 * p)  /grid.dx; //(p_j   - p)   /grid.dx;


	/*
	primitiveDerivativesWind[0] = (rho - rhoWind)      /grid.dx;
	primitiveDerivativesWind[1] = (vx  - velWind)      /grid.dx;
	primitiveDerivativesWind[2] = (p   - pressureWind) /grid.dx;

	setTransform(transform, rho, vx, p);
	setTransformInverse(transformInverse, rho, vx, p);

	charDerivatives     = matrixMultiply(transform, primitiveDerivatives);
	charDerivativesWind = matrixMultiply(transform, primitiveDerivativesWind);

	charDerivativesMixed[0] = charDerivatives[0];     // Characteristic travelling at v - c
	charDerivativesMixed[1] = charDerivativesWind[1]; // Characteristic travelling at v
	charDerivativesMixed[2] = charDerivativesWind[2]; //Characteristic travelling at v + c

	primitiveDerivativesMixed = matrixMultiply(transformInverse, charDerivativesMixed);
	 */

	double l1 = (vx - soundSpeed) * (primitiveDerivatives[2] - rho * soundSpeed * primitiveDerivatives[1]);

	std::cout << "L1 = " << l1 << " PrimDeriv1 = " << primitiveDerivatives[1] << " PrimDeriv2 = " << primitiveDerivatives[2] << std::endl;
	/*
	rhoGhost = rho - grid.dx * primitiveDerivativesMixed[0];
	velGhost = vx  - grid.dx * primitiveDerivativesMixed[1];
	pGhost   = p   - grid.dx * primitiveDerivativesMixed[2];
	*/

	rhoGhost = rhoWind;
	velGhost = velWind;
	//pGhost   = p - grid.dx * (l1 * vx / (vx * vx - soundSpeed * soundSpeed));
	pGhost   = p - grid.dx * (l1 * velWind / (velWind * velWind - soundSpeed * soundSpeed));

	grid.quantities[i][EquationsEuler::DENS]   = rhoGhost;
	grid.quantities[i][EquationsEuler::XMOM]   = rhoGhost * velGhost;
	grid.quantities[i][EquationsEuler::ENERGY] = (static_cast<EquationsEuler*>(&equations))->totalEnergy(pGhost,rhoGhost * std::pow(velGhost, 2.));

}


double BoundaryWind::getSoundSpeed(double gamma, double density, double pressure){
	if (density == 0)
        throw std::invalid_argument("Wind density cannot be zero.");

	return std::sqrt(gamma * pressure / density);
}

std::vector<double> BoundaryWind::matrixMultiply(std::vector<std::vector<double> > matrix, std::vector<double> vector){
	std::vector<double> product (3, 0.0);

	for(int i = 0; i <= 2; i++)
		for(int j = 0; j <= 2; j++)
			product[i] += matrix[i][j] * vector[j];

	return product;
}



BoundaryWind::~BoundaryWind() {
	// TODO Auto-generated destructor stub
}

