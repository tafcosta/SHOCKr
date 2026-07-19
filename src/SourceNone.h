/*
 * SourceNone.h
 *
 *  Created on: 27 Sept 2025
 *      Author: Tiago Costa
 */

#ifndef SRC_SOURCENONE_H_
#define SRC_SOURCENONE_H_

#include "Source.h"

class SourceNone: public Source {
public:
	SourceNone(Grid& grid, Equations& equations) : Source(grid, equations){};
	virtual ~SourceNone();

	std::vector<double> getSource(std::vector<double>& quantities, double radialDistance);

};

#endif /* SRC_SOURCENONE_H_ */
