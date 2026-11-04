/*
 * BoundaryWind.h
 *
 *  Created on: 22 Dec 2023
 *      Author: Tiago Costa
 */

#ifndef SRC_BOUNDARYWINDTMP_H_
#define SRC_BOUNDARYWINDTMP_H_

#include "Boundary.h"
#include "EquationsEuler.h"
#include "Grid.h"

class BoundaryWind: public Boundary {
public:
	BoundaryWind(double rhoWind, double velWind, double pressureWind, Grid& grid, EquationsEuler& equations) \
	: Boundary(grid, equations), rhoWind(rhoWind), velWind(velWind), pressureWind(pressureWind) {};

	virtual ~BoundaryWind();
	void setBoundaries(double time) override;

	// Outer boundary: false = zero gradient (copy the last cell), true = keep the
	// ghost cells at their initial values (holds a hydrostatic atmosphere in place)
	bool fixedOuterBoundary = false;

protected:
	double rhoWindDecay, pressureWindDecay, rhoWind, velWind, pressureWind;

	void doSubsonicWindGross(int i);
	void doSupersonicWind(int i);

	double getSoundSpeed(double gamma, double density, double pressure);
	std::vector<double> matrixMultiply(std::vector<std::vector<double> > matrix, std::vector<double> vector);
};

#endif /* SRC_BOUNDARYWINDTMP_H_ */
