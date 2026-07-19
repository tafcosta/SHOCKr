/*
 * ShockFinder.h
 *
 *  Created on: 16 Jan 2024
 *      Author: Tiago Costa
 */

#ifndef SRC_SHOCKFINDER_H_
#define SRC_SHOCKFINDER_H_

#include "Equations.h"
#include "Grid.h"
#include <vector>

class ShockFinder {
public:
	ShockFinder(Grid& grid, Equations& equations);
	virtual ~ShockFinder();
	virtual std::vector<int> findShockZones(double time, const std::string& filename){return std::vector<int> (grid.nx, 0);};

	Grid& grid;
	Equations& equations;


	std::vector<int> contact;
	std::vector<std::vector<double> > gradients;
	std::vector<double> divV;
	std::vector<int> shock;

};

#endif /* SRC_SHOCKFINDER_H_ */
