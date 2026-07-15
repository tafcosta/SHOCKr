/*
 * ShockFinderEulerPassiveScalar.cpp
 *
 *  Created on: 16 Jan 2024
 *      Author: Tiago Costa
 */

#include <cmath>
#include <iostream>
#include <fstream>

#include "ShockFinder.h"
#include "ShockFinderEuler.h"
#include "EquationsEulerPassiveScalar.h"

std::vector<int> ShockFinderEuler::findShockZones(double time, const std::string& filename){
    gradients = std::vector< std::vector<double> >(grid.nx + 2*grid.nGhost,
                                                 std::vector<double>(2, 0.0));

    divV    = std::vector<double>(grid.nx + 2*grid.nGhost, 0.0);
    shock   = std::vector<int>(grid.nx + 2*grid.nGhost, 0);
    contact = std::vector<int>(grid.nx + 2*grid.nGhost, 0);

    std::ofstream outFile("shock_output.txt", std::ios::app);

    if (!outFile.is_open()) {
        std::cerr << "Error opening shock_output.txt\n";
        return shock;
    }


    for (int i = grid.minXIndex; i <= grid.maxXIndex; ++i) {

        calculateGradients(i);
        calculateDivV(i);
        detectShockZone(i,
                        divV[i],
                        gradients[i][DENS],
                        gradients[i][TEMP]);
    }

    std::vector<int> starts;
    std::vector<int> ends;

    bool inShock = false;

    for (int i = grid.minXIndex; i <= grid.maxXIndex; ++i) {

        if (shock[i] && !inShock) {
            starts.push_back(i);
            inShock = true;
        }

        if (!shock[i] && inShock) {
            ends.push_back(i-1);
            inShock = false;
        }
    }

    if (inShock)
        ends.push_back(grid.maxXIndex);

    std::vector<int> goodStarts;
    std::vector<int> goodEnds;

    for (size_t i = 0; i < starts.size(); ++i) {

        int nCells = ends[i] - starts[i] + 1;

        if (nCells >= 3) {
            goodStarts.push_back(starts[i]);
            goodEnds.push_back(ends[i]);
        }
    }


    if (goodStarts.size() >= 2){
        writeShockOutput(time, goodStarts, goodEnds);
    }

    return shock;
}

void ShockFinderEuler::detectShockZone(int i, double divV_i, double gradientDens_i, double gradientTemp_i) {
	if (divV_i < 0 && (gradientTemp_i * gradientDens_i > 0))
		shock[i] = 1;
}

void ShockFinderEuler::calculateGradients(int i) {
	double rho_i, rho_j, p_i, p_j, rhoV2_i, rhoV2_j, T_i, T_j;

	rho_i   = grid.quantities[i][EquationsEulerPassiveScalar::DENS];
	rho_j   = grid.quantities[i + 1][EquationsEulerPassiveScalar::DENS];

	rhoV2_i = std::pow(grid.quantities[i][EquationsEulerPassiveScalar::XMOM], 2.) / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
	rhoV2_j = std::pow(grid.quantities[i + 1][EquationsEulerPassiveScalar::XMOM], 2.) / grid.quantities[i + 1][EquationsEulerPassiveScalar::DENS];
	p_i     = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i][EquationsEulerPassiveScalar::ENERGY], rhoV2_i);
	p_j     = (static_cast<EquationsEulerPassiveScalar*>(&equations))->getPressure(grid.quantities[i + 1][EquationsEulerPassiveScalar::ENERGY], rhoV2_j);

	T_i     = p_i/rho_i;
	T_j     = p_j/rho_j;

	gradients[i][DENS] = (rho_j - rho_i) / (grid.getX(i + 1) - grid.getX(i));
	gradients[i][TEMP] = (T_j - T_i)     / (grid.getX(i + 1) - grid.getX(i));
}


void ShockFinderEuler::calculateDivV(int i) {
	double u_i, u_j;

    u_i     = grid.quantities[i][EquationsEulerPassiveScalar::XMOM]     / grid.quantities[i][EquationsEulerPassiveScalar::DENS];
    u_j     = grid.quantities[i + 1][EquationsEulerPassiveScalar::XMOM] / grid.quantities[i + 1][EquationsEulerPassiveScalar::DENS];

	divV[i] = (u_j * pow(grid.getX(i + 1), 2.) - u_i * pow(grid.getX(i), 2.)) / (grid.getX(i + 1) - grid.getX(i)) / pow(grid.getX(i), 2.);
}

double ShockFinderEuler::getKineticFlux(double rho, double velocity, double shockVelocity)
{
    double vrel = std::abs(velocity - shockVelocity);
    return 0.5 * rho * vrel * vrel * vrel;
}

void ShockFinderEuler::writeShockOutput(
    double time,
    const std::vector<int>& goodStarts,
    const std::vector<int>& goodEnds)
{
    std::ofstream outFile("shock_output.txt", std::ios::app);

    if (!outFile.is_open()) {
        std::cerr << "Error opening shock_output.txt\n";
        return;
    }

    double reverseShock = getShockPosition(goodStarts.front(), goodEnds.front());

    double forwardShock = getShockPosition(goodStarts.back(), goodEnds.back());

    outFile << time << " "
            << reverseShock << " "
            << forwardShock << '\n';
}

double ShockFinderEuler::getShockPosition(int start, int end)
{
    double sum = 0.0;
    double weight = 0.0;

    for (int i = start; i <= end; ++i) {

        double w = std::max(0.0, -divV[i]);

        sum += w * grid.getX(i);
        weight += w;
    }

    if (weight > 0.0)
        return sum / weight;

    return 0.5 * (grid.getX(start) + grid.getX(end));
}

ShockFinderEuler::~ShockFinderEuler() {
	// TODO Auto-generated destructor stub
}

