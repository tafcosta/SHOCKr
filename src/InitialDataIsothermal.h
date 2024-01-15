/*
 * InitialDataIsothermal.h
 *
 *  Created on: 7 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATAISOTHERMAL_H_
#define SRC_INITIALDATAISOTHERMAL_H_

#include "InitialData.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"

class InitialDataIsothermal: public InitialData {
public:
	InitialDataIsothermal(Grid& grid, EquationsEuler& equations) : InitialData(grid, equations){};
	virtual ~InitialDataIsothermal();
	void setInitialData() override;
};

#endif /* SRC_INITIALDATAISOTHERMAL_H_ */
