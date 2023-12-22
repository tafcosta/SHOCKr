/*
 * BoundaryWind.h
 *
 *  Created on: 22 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_BOUNDARYWIND_H_
#define SRC_BOUNDARYWIND_H_

#include "Boundary.h"
#include "Grid.h"

class BoundaryWind: public Boundary {
public:
	BoundaryWind(Grid& grid,Equations& equations) : Boundary(grid,equations){};
	virtual ~BoundaryWind();
	void setBoundaries() override;
};

#endif /* SRC_BOUNDARYWIND_H_ */
