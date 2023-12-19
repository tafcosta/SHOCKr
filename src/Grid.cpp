/*
 * Grid.cpp
 *
 *  Created on: 19 Dec 2023
 *      Author: ntc132
 */

#include "Grid.h"

Grid::Grid(double xmin, double xmax, int nGhost, int nx) {
	this->xmin = xmin;
	this->xmax = xmax;
	this->nGhost = nGhost;
	this->nx = nx;

	this->quantities = std::vector<std::vector<double> > (nx + 2*nGhost, std::vector<double>(nCons, 0.0));
	this->fluxes = std::vector<std::vector<double> > (nx + 2*nGhost + 1, std::vector<double>(nCons, 0.0));

	dx = (xmax - xmin)/nx;
	xMidpoint = (xmax + xmin)/2;
	minXIndex = nGhost;
	maxXIndex = nGhost + nx - 1;
}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

