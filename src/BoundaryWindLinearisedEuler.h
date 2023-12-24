/*
 * BoundaryWindLinearisedEuler.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_BOUNDARYWINDLINEARISEDEULER_H_
#define SRC_BOUNDARYWINDLINEARISEDEULER_H_

#include "Boundary.h"
#include "Equations.h"
#include "EquationsLinearisedEuler.h"
#include "Grid.h"
#include "InitialDataHomogeneousLinearisedEuler.h"

class BoundaryWindLinearisedEuler: public Boundary {
public:
	BoundaryWindLinearisedEuler(Grid& grid, EquationsLinearisedEuler& equations, InitialDataHomogeneousLinearisedEuler& initialdata) : initialdata(initialdata), Boundary(grid, equations){};
	virtual ~BoundaryWindLinearisedEuler();

	void setBoundaries() override;
	InitialDataHomogeneousLinearisedEuler initialdata;
};

#endif /* SRC_BOUNDARYWINDLINEARISEDEULER_H_ */
