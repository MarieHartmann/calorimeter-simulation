#ifndef CaloSimulation_h
#define CaloSimulation_h

/**
 * CaloSimulation
 * Implements the simulation of the calorimter.
 */

#include "CellAddress.h"
#include "CaloCell.h"
#include <vector>
#include <map>

class CaloSimulation
{
public:
	CaloSimulation();

	// Add the calorimeter cells to the vector of cell caldata.
	void CalorimeterData(std::vector<CaloCell>& caldata) const;

	// Simulate a shower of a given energy, starting from the impact point (x,y)
	// of the electron at the front end of the calorimeter.
	// TODO: to be implemented.
	void SimulateShower(float x, float y, float energy);

	// Print all the cells.
	// TODO: to be implemented.
	friend std::ostream& operator<<(std::ostream& os, const CaloSimulation& cs);

private: // TODO: to be completed.

};

#endif
