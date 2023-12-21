/*
 * Grid.h
 *
 *  Created on: 19 Dec 2023
 *      Author: ntc132
 */
#include <vector>
#include "Equations.h"

#ifndef SRC_GRID_H_
#define SRC_GRID_H_

class Grid {
public:
	Grid(double xmin, double xmax, int nGhost, int nx, Equations& equations);
	virtual ~Grid();

	double dx, xMidpoint;
	double xmin, xmax;
	int minXIndex, maxXIndex;
	int nx, nGhost;

	std::vector<std::vector<double> > quantities;
	std::vector<std::vector<double> > fluxes;

	double getX(int cellIndex){
		double cellCentre = xmin + (cellIndex - minXIndex) * dx + dx/2.;
		return cellCentre;
	}

	virtual void update(double dt){};

	Equations equations;


private:
};

#endif /* SRC_GRID_H_ */
