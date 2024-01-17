/*
 * ShockFinder.h
 *
 *  Created on: 16 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_SHOCKFINDER_H_
#define SRC_SHOCKFINDER_H_

#include "Equations.h"
#include "Grid.h"

class ShockFinder {
public:
	ShockFinder(Grid& grid, Equations& equations);
	virtual ~ShockFinder();
	virtual void findShockZones(void){};
	virtual void findShockDirection(void){};
	virtual void calculateGradients(void){};

	Grid& grid;
	Equations& equations;
};

#endif /* SRC_SHOCKFINDER_H_ */
