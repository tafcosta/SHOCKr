/*
 * GridRadial.cpp
 *
 *  Created on: 20 Dec 2023
 *      Author: ntc132
 */

#include "GridRadial.h"
#include "Grid.h"

void GridRadial::update(double dt) {
	for(int i = minXIndex; i <= maxXIndex; i++)
		for(int k = 0; k < nCons; k++)
			quantities[i][k]  = quantities[i][k] - dt/dx * (fluxes[i + 1][k] - fluxes[i][k]);
	}

GridRadial::~GridRadial() {
	// TODO Auto-generated destructor stub
}

