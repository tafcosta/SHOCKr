/*
 * OutputLinearisedEuler.h
 *
 *  Created on: 23 Dec 2023
 *      Author: ntc132
 */

#ifndef SRC_OUTPUTLINEARISEDEULER_H_
#define SRC_OUTPUTLINEARISEDEULER_H_

#include "Output.h"

class OutputLinearisedEuler: public Output {
public:
	OutputLinearisedEuler(Grid& grid, Equations& equations) : Output(grid, equations) {};;
	virtual ~OutputLinearisedEuler();

	void makeOutput(const std::string& filename) override;
};

#endif /* SRC_OUTPUTLINEARISEDEULER_H_ */
