/*
 * SourceNone.h
 *
 *  Created on: 27 Sept 2025
 *      Author: ntc132
 */

#ifndef SRC_SOURCENONE_H_
#define SRC_SOURCENONE_H_

#include "Source.h"

class SourceNone: public Source {
public:
	SourceNone(Grid& grid, Equations& equations) : Source(grid, equations){};
	virtual ~SourceNone();
};

#endif /* SRC_SOURCENONE_H_ */
