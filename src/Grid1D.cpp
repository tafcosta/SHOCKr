/*
 * Grid1D.cpp
 *
 *  Created on: 19 Dec 2023
 *      Author: ntc132
 */

#include "Grid.h"
#include "Grid1D.h"

void Grid1D::update(double dt) {
	for(int i = minXIndex; i <= maxXIndex; i++){
		for(int j = 0; j < equations.nCons(); j++)
			quantities[i][j]  = quantities[i][j] - dt/dx * (fluxes[i + 1][j] - fluxes[i][j]);

		equations.postProcessor(quantities[i], dt);

		}
	}

Grid1D::~Grid1D() {
}

