/*
 * Output.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#include "Equations.h"
#include "Grid.h"

#include <string>

#ifndef SRC_OUTPUT_H_
#define SRC_OUTPUT_H_

class Output {
public:
	Output(Grid& grid, Equations& equations);
	virtual ~Output();
	virtual void makeOutput(const std::string& filename){};

	Grid& grid;
	Equations& equations;
};

#endif /* SRC_OUTPUT_H_ */
