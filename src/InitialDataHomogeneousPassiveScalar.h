/*
 * InitialDataHomogeneousPassiveScalar.h
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_INITIALDATAHOMOGENEOUSPASSIVESCALAR_H_
#define SRC_INITIALDATAHOMOGENEOUSPASSIVESCALAR_H_

#include "Equations.h"
#include "EquationsEulerPassiveScalar.h"
#include "Grid.h"
#include "InitialDataHomogeneous.h"

class InitialDataHomogeneousPassiveScalar: public InitialData {
public:
	InitialDataHomogeneousPassiveScalar(Grid& grid, EquationsEulerPassiveScalar& equations) : InitialData(grid, equations){};;
	virtual ~InitialDataHomogeneousPassiveScalar();
	void setInitialData() override;
};

#endif /* SRC_INITIALDATAHOMOGENEOUSPASSIVESCALAR_H_ */
