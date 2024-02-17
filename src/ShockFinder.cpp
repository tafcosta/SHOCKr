/*
 * ShockFinder.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: ntc132
 */

#include "Equations.h"
#include "Grid.h"
#include "ShockFinder.h"

ShockFinder::ShockFinder(Grid& grid, Equations& equations) : grid(grid), equations(equations) {
	gradients = std::vector<std::vector<double> > ( + 2*grid.nGhost, std::vector<double>(2., 0.0));
	divV      = std::vector<double>(grid.nx + 2*grid.nGhost, 0.0);
	shock     = std::vector<int>(grid.nx + 2*grid.nGhost, 0);
}

ShockFinder::~ShockFinder() {
	// TODO Auto-generated destructor stub
}

