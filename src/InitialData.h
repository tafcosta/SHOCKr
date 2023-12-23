/*
 * InitialData.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "Equations.h"
#include "Grid.h"

#ifndef SRC_INITIALDATA_H_
#define SRC_INITIALDATA_H_

class InitialData {
public:
	InitialData(Grid& grid, Equations& equations);
	virtual ~InitialData();

	Grid& grid;
	Equations& equations;
	virtual void setInitialData(){};
};

#endif /* SRC_INITIALDATA_H_ */
