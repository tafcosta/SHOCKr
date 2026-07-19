/*
 * InitialDataRadial.h
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#ifndef SRC_INITIALDATARADIAL_H_
#define SRC_INITIALDATARADIAL_H_

#include "Equations.h"
#include "EquationsEuler.h"
#include "GasProfile.h"
#include "Grid.h"
#include "InitialData.h"

class InitialDataRadial: public InitialData {
public:

    InitialDataRadial(Grid& grid, EquationsEuler& equations, GasProfile& gas) : InitialData(grid, equations), gas(gas) {}
	virtual ~InitialDataRadial();

    void setInitialData() override;

protected:

    GasProfile& gas;
};

#endif /* SRC_INITIALDATARADIAL_H_ */
