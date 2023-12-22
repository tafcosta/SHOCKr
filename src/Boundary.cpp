/*
 * Boundary.cpp
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#include "Boundary.h"
#include "Equations.h"
#include "Grid.h"

Boundary::Boundary(Grid& grid, Equations& equations) : grid(grid), equations(equations) {

}

Boundary::~Boundary() {
	// TODO Auto-generated destructor stub
}

