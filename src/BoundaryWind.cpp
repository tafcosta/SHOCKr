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

	double rho, rho_j, vx, vel_j, p, p_j;
	double rhoGhost, velGhost, pGhost;

	std::vector<double> charDerivatives (3, 0.0), charDerivativesWind (3, 0.0), charDerivativesMixed (3, 0.0);
	std::vector<double> primitiveDerivatives (3, 0.0), primitiveDerivativesWind (3, 0.0), primitiveDerivativesMixed (3, 0.0);
	std::vector<std::vector<double> > transform (3, std::vector<double>(3, 0.0));
	std::vector<std::vector<double> > transformInverse (3, std::vector<double>(3, 0.0));

	double gamma = (static_cast<EquationsEuler*>(&equations))->gamma;

	rho   = grid.quantities[grid.minXIndex][EquationsEuler::DENS];
	rho_j = grid.quantities[grid.minXIndex + 1][EquationsEuler::DENS];
	vx    = grid.quantities[grid.minXIndex][EquationsEuler::XMOM]/grid.quantities[grid.minXIndex][EquationsEuler::DENS];
	vel_j = grid.quantities[grid.minXIndex + 1][EquationsEuler::XMOM]/grid.quantities[grid.minXIndex + 1][EquationsEuler::DENS];
	p     = (static_cast<EquationsEuler*>(&equations))->getPressure(grid.quantities[grid.minXIndex][EquationsEuler::ENERGY],     rho   * std::pow(vx, 2.));
	p_j   = (static_cast<EquationsEuler*>(&equations))->getPressure(grid.quantities[grid.minXIndex + 1][EquationsEuler::ENERGY], rho_j * std::pow(vel_j, 2.));

	primitiveDerivatives[0]     = (rho_j - rho) /grid.dx;
	primitiveDerivatives[1]     = (vel_j - vx)  /grid.dx;
	primitiveDerivatives[2]     = (p_j   - p)   /grid.dx;

	primitiveDerivativesWind[0] = (rho - rhoWind)    /grid.dx;
	primitiveDerivativesWind[1] = (vx - velWind)     /grid.dx;
	primitiveDerivativesWind[2] = (p - pressureWind) /grid.dx;



	transform[0][0] = 0.;
	transform[0][1] = ((-std::sqrt(gamma * p * rho) + (-1 + gamma) * rho * vx) * (gamma * p - std::sqrt(gamma * p * rho) * vx)                       \
			* (2 * gamma * p * std::sqrt(gamma * p * rho) + gamma * rho * std::pow(vx, 2.) * (5 * std::sqrt(gamma * p * rho) - 2 * rho * vx)         \
			+ rho*std::pow(vx,2)*(-3*std::sqrt(gamma*p*rho) + rho*vx) +  std::pow(gamma,2)*rho*std::pow(vx,2)*(-2*std::sqrt(gamma*p*rho) + rho*vx))) \
			/ (4.*(-1 + gamma) * gamma * p * rho * (rho * std::pow(vx, 2.) + std::pow(gamma, 2.) * rho * std::pow(vx, 2.) - gamma*(p + 2 * rho * std::pow(vx, 2.))));
	transform[0][2] = (rho * (-((gamma * p) / std::sqrt(gamma * p * rho)) + vx) * (-2 * gamma * p * std::sqrt(gamma * p * rho) + std::pow(gamma, 2)  \
			* rho * std::pow(vx, 2.)*(2*std::sqrt(gamma*p*rho) - rho*vx) + rho*std::pow(vx,2)*(3*std::sqrt(gamma*p*rho) - rho*vx)                    \
			+ gamma * rho * std::pow(vx, 2.)*(-5 * std::sqrt(gamma * p * rho) + 2 * rho * vx)) * (std::sqrt(gamma * p * rho) * vx + gamma * (p - std::sqrt(gamma * p * rho) * vx)))  \
			/ (4.* (-1 + gamma) * std::pow(gamma*p*rho, 1.5) * (rho * std::pow(vx, 2.) + std::pow(gamma, 2.) * rho * std::pow(vx, 2.) - gamma * (p + 2 * rho*std::pow(vx, 2.))));

	transform[1][0] = std::pow(vx, 3.) / 2.;
	transform[1][1] = 0.0;
	transform[1][2] = -0.5 * (rho * std::pow(vx,3)) / (gamma * p);

	transform[2][0] = 0.0;
	transform[2][1] = ((std::sqrt(gamma * p * rho) + (-1 + gamma) * rho * vx) * (gamma * p + std::sqrt(gamma * p * rho) *vx)                     \
			* (std::pow(gamma,2)*rho*std::pow(vx, 2.) * (2 * std::sqrt(gamma * p * rho) + rho * vx) + rho * std::pow(vx, 2.) * (3 * std::sqrt(gamma * p * rho) + rho*vx) \
			- gamma*(2*p*std::sqrt(gamma*p*rho) + rho*std::pow(vx,2)*(5*std::sqrt(gamma*p*rho) + 2*rho*vx))))                                    \
			/ (4.*(-1 + gamma)*gamma*p*rho*(rho*std::pow(vx,2) + std::pow(gamma,2)*rho*std::pow(vx,2) - gamma*(p + 2*rho*std::pow(vx,2))));
	transform[2][2] = (rho*((gamma*p)/std::sqrt(gamma*p*rho) + vx)*(-(std::sqrt(gamma*p*rho)*vx) + gamma*(p + std::sqrt(gamma*p*rho)*vx))        \
			* (std::pow(gamma,2)*rho*std::pow(vx,2)*(2*std::sqrt(gamma*p*rho) + rho*vx) + rho*std::pow(vx,2)*(3*std::sqrt(gamma*p*rho) + rho*vx) \
			- gamma*(2*p*std::sqrt(gamma*p*rho) + rho*std::pow(vx,2)*(5*std::sqrt(gamma*p*rho) + 2*rho*vx))))                                    \
			/ (4.*(-1 + gamma)*std::pow(gamma*p*rho,1.5)*(rho*std::pow(vx,2) + std::pow(gamma,2)*rho*std::pow(vx,2) - gamma*(p + 2*rho*std::pow(vx,2))));


	transformInverse[0][0] = 2.0 * (-1 + gamma) * std::pow(rho, 2.) / (-2 * gamma * p * std::sqrt(gamma * p * rho)                                          \
			+ 2 * std::pow(gamma, 2.) * p * rho * vx + rho * std::pow(vx, 2) * (3 * std::sqrt(gamma * p * rho) - rho * vx)                                  \
			+ gamma * rho * std::pow(vx, 2) * (-3 * std::sqrt(gamma * p * rho) + rho * vx));
	transformInverse[0][1] = 2.0 / std::pow(vx, 3.);
	transformInverse[0][2] = (2*(-1 + gamma)*std::pow(rho,2))                                                                                               \
			/ (2 * gamma * p * std::sqrt(gamma * p * rho) + 2*std::pow(gamma,2) * p * rho * vx - rho*std::pow(vx,2) * (3*std::sqrt(gamma*p*rho) + rho * vx) \
			+ gamma * rho * std::pow(vx,2.) * (3 * std::sqrt(gamma * p * rho) + rho * vx));

	transformInverse[1][0] = (2*(-1 + gamma)*gamma*p)/(rho*std::sqrt(gamma*p*rho)*std::pow(vx,3) - gamma*rho*std::pow(vx,2)*(3*p + std::sqrt(gamma*p*rho)*vx) +
	       std::pow(gamma,2)*p*(2*p + vx*(-2*std::sqrt(gamma*p*rho) + 3*rho*vx)));
	transformInverse[1][1] = 0.;
	transformInverse[1][2] = (2*(-1 + gamma)*gamma*p)/(-(rho*std::sqrt(gamma*p*rho)*std::pow(vx,3)) + gamma*rho*std::pow(vx,2)*(-3*p + std::sqrt(gamma*p*rho)*vx) +
	       std::pow(gamma,2)*p*(2*p + vx*(2*std::sqrt(gamma*p*rho) + 3*rho*vx)));

	transformInverse[2][0] = 1.0 / (std::sqrt(gamma*p*rho)/(rho - gamma*rho) + (gamma*vx)/(-1 + gamma) + (std::pow(vx,2)*(-3*std::sqrt(gamma*p*rho) + rho*vx))/(2.*gamma*p));
	transformInverse[2][1] = 0.0;
	transformInverse[2][2] = 1.0 / ((gamma*p)/((-1 + gamma)*std::sqrt(gamma*p*rho)) + (gamma*vx)/(-1 + gamma) + (3*rho*std::pow(vx,2))/(2. * std::sqrt(gamma*p*rho)) + (rho * std::pow(vx,3))/(2.*gamma*p));




	charDerivatives     = matrixMultiply(transform, primitiveDerivatives);
	charDerivativesWind = matrixMultiply(transform, primitiveDerivativesWind);

	charDerivativesMixed[0] = charDerivatives[0];            // Characteristic travelling at v - c
	charDerivativesMixed[1] = 0. * charDerivativesWind[1]; // Characteristic travelling at v
	charDerivativesMixed[2] = 0. * charDerivativesWind[2]; //Characteristic travelling at v + c

	primitiveDerivativesMixed = matrixMultiply(transformInverse, charDerivativesMixed);

	rhoGhost = rho - grid.dx * primitiveDerivativesMixed[0];
	velGhost = vx  - grid.dx * primitiveDerivativesMixed[1];
	pGhost   = p   - grid.dx * primitiveDerivativesMixed[2];

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

