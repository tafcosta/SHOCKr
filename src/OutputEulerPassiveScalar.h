/*
 * OutputEulerPassiveScalar.h
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_OUTPUTEULERPASSIVESCALAR_H_
#define SRC_OUTPUTEULERPASSIVESCALAR_H_

#include "EquationsEulerPassiveScalar.h"
#include "Grid.h"
#include "Output.h"

class OutputEulerPassiveScalar: public Output {
public:
	OutputEulerPassiveScalar(Grid& grid, EquationsEulerPassiveScalar& equations) : Output(grid, equations) {};
	virtual ~OutputEulerPassiveScalar();

	void makeOutput(const std::string& filename) override;

};

#endif /* SRC_OUTPUTEULERPASSIVESCALAR_H_ */
