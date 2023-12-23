/*
 * Boundary.h
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#include "Grid.h"

#ifndef BOUNDARY_H_
#define BOUNDARY_H_

class Boundary{
public:
	Boundary(Grid& grid, Equations& equations);
	virtual ~Boundary();

	Grid& grid;
	Equations& equations;
	virtual void setBoundaries(){};

};

#endif /* BOUNDARY_H_ */
