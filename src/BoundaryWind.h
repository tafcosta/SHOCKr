/*
 * BoundaryWind.h
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_BOUNDARYWINDTMP_H_
#define SRC_BOUNDARYWINDTMP_H_

#include "Boundary.h"
#include "EquationsEuler.h"
#include "Grid.h"

class BoundaryWind: public Boundary {
public:
	BoundaryWind(double rhoWind, double velWind, double pressureWind, Grid& grid, EquationsEuler& equations) : Boundary(grid, equations), rhoWind(rhoWind), velWind(velWind), pressureWind(pressureWind) {};
	virtual ~BoundaryWind();
	void setBoundaries() override;

	double rhoWind, velWind, pressureWind;
};

#endif /* SRC_BOUNDARYWINDTMP_H_ */
