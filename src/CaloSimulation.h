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

using namespace std;

class CaloSimulation
{
public:

	CaloSimulation();

	~CaloSimulation();

	// Add the calorimeter cells to the vector of cell caldata.
	void CalorimeterData();

  // Return caldata
  vector<CaloCell> caldata() const;

	// Give the index in caldata of the point.
	int caldataIndex(int ix, int iy, int iz) const;

	// Simulate a shower of a given energy, starting from the impact point (x,y)
	// of the electron at the front end of the calorimeter.
	// TODO: to be implemented.
	void SimulateShower(float x, float y, float energy);

	// Print all the cells.
	// TODO: to be implemented.
	friend ostream& operator<<(ostream& os, const CaloSimulation& cs);

private: // TODO: to be completed.

   vector<CaloCell> m_caldata;
};

#endif
