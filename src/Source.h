/*
 * Source.h
 *
 *  Created on: 27 Sept 2025
 *      Author: Tiago Costa
 */

#ifndef SRC_SOURCE_H_
#define SRC_SOURCE_H_

#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"

class Source {
public:
	Source(Grid& grid, Equations& equations);
	virtual ~Source();

	Grid& grid;
	Equations& equations;

	void setSources();
	virtual std::vector<double> getSource(std::vector<double>& quantities, double radialDistance){return std::vector<double>(equations.nCons(), 0.0);};

};

#endif /* SRC_SOURCE_H_ */
