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
	double rhoV2;
	double p;

	for(int i = minXIndex; i <= maxXIndex; i++){
		rhoV2 = quantities[i][EquationsEuler::XMOM] * quantities[i][EquationsEuler::XMOM] / quantities[i][EquationsEuler::DENS];
		p = (static_cast<EquationsEuler*>(&equations))->getPressure(quantities[i][EquationsEuler::ENERGY], rhoV2);

		for(int k = 0; k < equations.nCons(); k++){
			xLeft   = getX(i) - dx/2.;
			xRight  = getX(i)+ dx/2.;
			dVolume = pow(xRight, 3) - pow(xLeft, 3);
			quantities[i][k]  = quantities[i][k] - dt/dVolume * 3 * (fluxes[i + 1][k] * pow(xRight, 2.) - fluxes[i][k] * pow(xLeft, 2.));
		}

		quantities[i][EquationsEuler::XMOM] += dt * 3 * 2./dVolume * dx * getX(i) * p;
	}
}

GridRadial::~GridRadial() {
	// TODO Auto-generated destructor stub
}

