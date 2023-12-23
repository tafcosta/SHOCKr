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

class BoundaryWindLinearisedEuler: public Boundary {
public:
	BoundaryWindLinearisedEuler(Grid& grid, EquationsLinearisedEuler& equations) : Boundary(grid, equations){};
	virtual ~BoundaryWindLinearisedEuler();

	void setBoundaries() override;
};

#endif /* SRC_BOUNDARYWINDLINEARISEDEULER_H_ */
