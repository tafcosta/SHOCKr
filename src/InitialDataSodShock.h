/*
 * InitialDataSodShock.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATASODSHOCK_H_
#define SRC_INITIALDATASODSHOCK_H_

#include "Equations.h"
#include "Grid.h"
#include "InitialData.h"

class InitialDataSodShock: public InitialData {
public:
	InitialDataSodShock(Grid& grid, Equations& equations) : InitialData(grid, equations){};
	virtual ~InitialDataSodShock();
	void setInitialData() override;
};

#endif /* SRC_INITIALDATASODSHOCK_H_ */
