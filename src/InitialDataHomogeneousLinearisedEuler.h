/*
 * InitialDataHomogeneousLinearisedEuler.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATAHOMOGENEOUSLINEARISEDEULER_H_
#define SRC_INITIALDATAHOMOGENEOUSLINEARISEDEULER_H_

#include "Equations.h"
#include "EquationsLinearisedEuler.h"
#include "Grid.h"
#include "InitialData.h"

class InitialDataHomogeneousLinearisedEuler: public InitialData {
public:
	InitialDataHomogeneousLinearisedEuler(Grid& grid, EquationsLinearisedEuler& equations) : InitialData(grid, equations){};
	virtual ~InitialDataHomogeneousLinearisedEuler();
	void setInitialData() override;
};

#endif /* SRC_INITIALDATAHOMOGENEOUSLINEARISEDEULER_H_ */
