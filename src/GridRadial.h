/*
 * GridRadial.h
 *
 *  Created on: 20 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_GRIDRADIAL_H_
#define SRC_GRIDRADIAL_H_

#include "Grid.h"

class GridRadial: public Grid {
public:
	GridRadial(double xmin, double xmax, int nGhost, int nx) : Grid(xmin, xmax, nGhost, nx){};
	void update(double dt) override;
	virtual ~GridRadial();
};

#endif /* SRC_GRIDRADIAL_H_ */
