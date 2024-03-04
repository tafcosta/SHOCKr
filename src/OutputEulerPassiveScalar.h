/*
 * OutputEulerPassiveScalar.h
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_OUTPUTEULERPASSIVESCALAR_H_
#define SRC_OUTPUTEULERPASSIVESCALAR_H_

#include "Equations.h"
#include "Grid.h"
#include "OutputEuler.h"

class OutputEulerPassiveScalar: public Output {
public:
	OutputEulerPassiveScalar(Grid& grid, Equations& equations) : Output(grid, equations) {};
	virtual ~OutputEulerPassiveScalar();

	void makeOutput(const std::string& filename, double time) override;

};

#endif /* SRC_OUTPUTEULERPASSIVESCALAR_H_ */
