/*
 * InitialDataHomogeneous.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATAHOMOGENEOUS_H_
#define SRC_INITIALDATAHOMOGENEOUS_H_

#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"
#include "InitialData.h"

class InitialDataHomogeneous: public InitialData {
public:
	InitialDataHomogeneous(Grid& grid, EquationsEuler& equations) : InitialData(grid, equations){};
	virtual ~InitialDataHomogeneous();
	void setInitialData() override;
};

#endif /* SRC_INITIALDATAHOMOGENEOUS_H_ */
