/*
 * Source.cpp
 *
 *  Created on: 27 Sept 2025
 *      Author: Tiago Costa
 */

#include "Source.h"

void Source::setSources(void){
	for(int i = grid.minXIndex; i <= grid.maxXIndex; i++)
		grid.sources[i] = getSource(grid.quantities[i], grid.getX(i));
}

Source::Source(Grid& grid, Equations& equations)  : grid(grid), equations(equations) {
	// TODO Auto-generated constructor stub

}

Source::~Source() {
	// TODO Auto-generated destructor stub
}

