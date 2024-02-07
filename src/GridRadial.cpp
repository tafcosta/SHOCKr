/*
 * GridRadial.cpp
 *
 *  Created on: 20 Dec 2023
 *      Author: ntc132
 */

#include "Equations.h"
#include "EquationsEuler.h"
#include "EquationsEulerPassiveScalar.h"
#include "GridRadial.h"
#include "Grid.h"
#include <math.h>
#include <cmath>
#include <iostream>

void GridRadial::update(double dt) {

	double dVolume, xLeft, xRight;
	double p, pLeft, pRight;

	for(int i = minXIndex; i <= maxXIndex; i++){
		p      = (static_cast<EquationsEuler*>(&equations))->getPressure(quantities[i]);
		pLeft  = (static_cast<EquationsEuler*>(&equations))->getPressure(quantities[i - 1]);
		pRight = (static_cast<EquationsEuler*>(&equations))->getPressure(quantities[i + 1]);

		for(int k = 0; k < equations.nCons(); k++){
			xLeft   = getX(i)-dx/2.;
			xRight  = getX(i)+dx/2.;
			dVolume = std::pow(xRight, 3) - std::pow(xLeft, 3);
			quantities[i][k]  = quantities[i][k] - dt/dVolume * 3 * (fluxes[i + 1][k] * pow(xRight, 2.) - fluxes[i][k] * pow(xLeft, 2.));
		}

		//quantities[i][EquationsEuler::XMOM] += dt * 3 * 2./dVolume * dx * getX(i) * p;
		quantities[i][EquationsEuler::XMOM] += dt * wellBalancedSource(3 * 2./dVolume * dx * getX(i-1) * pLeft, 3 * 2./dVolume * dx * getX(i) * p, 3 * 2./dVolume * dx * getX(i+1) * pRight, i);

	}
}

double GridRadial::wellBalancedSource(double sLeft, double sMid, double sRight, int i){

	std::vector<std::vector<double> > AconsPlus  (3, std::vector<double>(3, 0.0));
	std::vector<std::vector<double> > AconsMinus (3, std::vector<double>(3, 0.0));
	std::vector<std::vector<double> > invAcons   (3, std::vector<double>(3, 0.0));

	double c, rho, vx, p;
	double gamma = (static_cast<EquationsEuler*>(&equations))->gamma;
	double dVolume = std::pow(getX(i)+dx/2., 3) - std::pow(getX(i)-dx/2., 3);

	rho   = quantities[i][EquationsEuler::DENS];
	vx    = quantities[i][EquationsEuler::XMOM]/quantities[i][EquationsEuler::DENS];
	p     = (static_cast<EquationsEuler*>(&equations))->getPressure(quantities[i]);
	c     = std::sqrt(gamma * p / rho);

	double absvx = std::abs(vx);

	AconsPlus[0][0] = (2*absvx + ((absvx + c*(-3 + gamma) - absvx*gamma)*std::pow(vx,2))/std::pow(c,2))/4.;
	AconsPlus[0][1] = (std::pow(c,2) - c*(-2 + gamma)*vx + absvx*(-1 + gamma)*vx)/(2.*std::pow(c,2));
	AconsPlus[0][2] = ((-absvx + c)*(-1 + gamma))/(2.*std::pow(c,2));

	AconsPlus[1][0] = (vx*(2*(absvx - c)*std::pow(c,2) + std::pow(c,2)*(-3 + gamma)*vx + (absvx + 2*c*(-2 + gamma) - absvx*gamma)*std::pow(vx,2)))/
	(4.*std::pow(c,2));
	AconsPlus[1][1] = ((-1 + gamma)*std::pow(vx,2)*(absvx + vx) + std::pow(c + vx,2)*(c + vx - gamma*vx))/(2.*std::pow(c,2));
	AconsPlus[1][2] = ((-1 + gamma)*(std::pow(c,2) - absvx*vx + 2*c*vx))/(2.*std::pow(c,2));

	AconsPlus[2][0] = (vx*((-4*std::pow(c,4))/(-1 + gamma) - (2*std::pow(c,3)*(1 + gamma)*vx)/(-1 + gamma) - absvx*(-1 + gamma)*std::pow(vx,3) + c*(-5 + 3*gamma)*std::pow(vx,3) +
	  2*std::pow(c,2)*vx*(absvx + (-2 + gamma)*vx)))/(8.*std::pow(c,2));
	AconsPlus[2][1] = (std::pow(-1 + gamma,2)*std::pow(vx,3)*(absvx + vx) + (c + vx)*(c + vx - gamma*vx)*(2*std::pow(c,2) + 2*c*(-1 + gamma)*vx + (-1 + gamma)*std::pow(vx,2)))/
	(4.*std::pow(c,2)*(-1 + gamma));
	AconsPlus[2][2] = (2*c + 2*gamma*vx - ((absvx - 3*c)*(-1 + gamma)*std::pow(vx,2))/std::pow(c,2))/4.;

	AconsMinus[0][0] = (-2*absvx + ((-(c*(-3 + gamma)) + absvx*(-1 + gamma))*std::pow(vx,2))/std::pow(c,2))/4.;
	AconsMinus[0][1] = (1 + ((absvx + c*(-2 + gamma) - absvx*gamma)*vx)/std::pow(c,2))/2.;
	AconsMinus[0][2] = ((absvx - c)*(-1 + gamma))/(2.*std::pow(c,2));


	AconsMinus[1][0] = (vx*(2*std::pow(c,2)*(-absvx + c) + std::pow(c,2)*(-3 + gamma)*vx + (-2*c*(-2 + gamma) + absvx*(-1 + gamma))*std::pow(vx,2)))/
	(4.*std::pow(c,2));
	AconsMinus[1][1] = -0.5*(std::pow(c,3) + std::pow(c,2)*(-3 + gamma)*vx + c*(3 - 2*gamma)*std::pow(vx,2) + absvx*(-1 + gamma)*std::pow(vx,2))/std::pow(c,2);
	AconsMinus[1][2] = ((-1 + gamma)*(std::pow(c,2) + absvx*vx - 2*c*vx))/(2.*std::pow(c,2));


	AconsMinus[2][0] = (vx*(-4*std::pow(c,4) + 2*std::pow(c,2)*(absvx + c - absvx*gamma + c*gamma)*vx + 2*std::pow(c,2)*(-2 + gamma)*(-1 + gamma)*std::pow(vx,2) +
	  (c*(5 - 3*gamma) + absvx*(-1 + gamma))*(-1 + gamma)*std::pow(vx,3)))/(8.*std::pow(c,2)*(-1 + gamma));
	AconsMinus[2][1] = ((2*std::pow(c,2))/(-1 + gamma) - (2*c*vx)/(-1 + gamma) + (3 - 2*gamma)*std::pow(vx,2) + ((absvx - absvx*gamma + c*(-4 + 3*gamma))*std::pow(vx,3))/std::pow(c,2))/4.;
	AconsMinus[2][2] = (-2*c + 2*gamma*vx + ((absvx - 3*c)*(-1 + gamma)*std::pow(vx,2))/std::pow(c,2))/4.;


	double detAcons = -gamma * p * vx / rho + std::pow(vx,3);

	invAcons[0][0]  = -gamma * p / rho + ((3 + gamma) * std::pow(vx,2))/2.;
	invAcons[0][1]  = -gamma * vx;
	invAcons[0][2]  =  gamma - 1;

	invAcons[1][0] = -((gamma*p*vx)/rho) + std::pow(vx,3);
	invAcons[1][1] = 0.;
	invAcons[1][2] = 0.;

	invAcons[2][0] = -0.25 * ((-3 + gamma)*std::pow(vx,2)*(2*gamma*p + (-1 + gamma)*rho*std::pow(vx,2)))/((-1 + gamma)*rho);
	invAcons[2][1] = (gamma * p * vx)/(rho - gamma * rho) + ((-2 + gamma) * std::pow(vx,3)) / 2.;
	invAcons[2][2] = -0.5 * ((-3 + gamma)*std::pow(vx,2));

	for (int k = 0; k <= 2; k++)
		for (int j = 0; j <= 2; j++)
			invAcons[k][j] /= detAcons;

	std::vector<double> deltaLeft  (3, 0.);
	std::vector<double> deltaMid   (3, 0.);
	std::vector<double> deltaRight (3, 0.);

	for(int j = 0; j <= 2; j++){
		deltaLeft[j]  = (invAcons[j][1] * sLeft  * dVolume/3. - quantities[i-1][j] * 2 * dx * getX(i-1)) / (2 * getX(i - 1) * getX(i - 1) + dx * dx / 2.);
		deltaMid[j]   = (invAcons[j][1] * sMid   * dVolume/3. - quantities[i][j]   * 2 * dx * getX(i))   / (2 * getX(i)     * getX(i)     + dx * dx / 2.);
		deltaRight[j] = (invAcons[j][1] * sRight * dVolume/3. - quantities[i+1][j] * 2 * dx * getX(i+1)) / (2 * getX(i + 1) * getX(i + 1) + dx * dx / 2.);
	}

	double res = 0.;

	for(int j = 0; j <= 2; j++)
		res += 3 / dVolume * (AconsMinus[1][j] * (deltaMid[j] + deltaRight[j]) * std::pow(getX(i) + dx / 2., 2.) + AconsPlus[1][j] * (deltaMid[j] + deltaLeft[j]) * std::pow(getX(i) - dx / 2., 2.));

	return res;
}


GridRadial::~GridRadial() {
	// TODO Auto-generated destructor stub
}

