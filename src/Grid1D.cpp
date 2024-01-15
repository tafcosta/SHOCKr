/*
 * Grid1D.cpp
 *
 *  Created on: 19 Dec 2023
 *      Author: ntc132
 */

#include "Grid.h"
#include "Grid1D.h"

void Grid1D::update(double dt) {
	for(int i = minXIndex; i <= maxXIndex; i++)
		for(int k = 0; k < equations.nCons(); k++)
			quantities[i][k]  = quantities[i][k] - dt/dx * (fluxes[i + 1][k] - fluxes[i][k]);

	}

Grid1D::~Grid1D() {
	// TODO Auto-generated destructor stub
}

