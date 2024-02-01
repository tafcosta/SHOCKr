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
	BoundaryWind(double rhoWind, double velWind, double pressureWind, double rhoBackground, double velBackground, double pressureBackground, Grid& grid, EquationsEuler& equations) \
	: Boundary(grid, equations), rhoWind(rhoWind), velWind(velWind), pressureWind(pressureWind), rhoBackground(rhoBackground), velBackground(velBackground), pressureBackground(pressureBackground) {};

	virtual ~BoundaryWind();
	void setBoundaries() override;

protected:
	double rhoWind, velWind, pressureWind;
	double rhoBackground, velBackground, pressureBackground;

	void doSubsonicWind(int i);
	void doSubsonicWindGross(int i);
	void doSubsonicWindGrossRadial(int i);

	void doSupersonicWind(int i);
	void setTransform(std::vector<std::vector<double> >& transform, double rho, double vx, double p);
	void setTransformInverse(std::vector<std::vector<double> >& transformInverse, double rho, double vx, double p);

	double getSoundSpeed(double gamma, double density, double pressure);
	std::vector<double> matrixMultiply(std::vector<std::vector<double> > matrix, std::vector<double> vector);
};

#endif /* SRC_BOUNDARYWINDTMP_H_ */
