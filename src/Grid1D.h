/*
 * Grid1D.h
 *
 *  Created on: 19 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_GRID1D_H_
#define SRC_GRID1D_H_

#include "Grid.h"

class Grid1D: public Grid {
public:
	Grid1D(double xmin, double xmax, int nGhost, int nx) : Grid(xmin, xmax, nGhost, nx){};
	void update(double dt) override;
	virtual ~Grid1D();
};

#endif /* SRC_GRID1D_H_ */
