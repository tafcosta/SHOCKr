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
	GridRadial(double xmin, double xmax, int nGhost, int nx, Equations& equations) : Grid(xmin, xmax, nGhost, nx, equations){};
	void update(double dt) override;
	double wellBalancedSource(double sLeft, double sMid, double sRight, int i);
	virtual ~GridRadial();
};

#endif /* SRC_GRIDRADIAL_H_ */
