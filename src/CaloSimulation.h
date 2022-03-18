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

	// Clean the calorimeter (all energies set to 0)
	void ClearCalorimeter();

  // Return caldata
  vector<CaloCell> caldata() const;

	// Give the index in caldata of the point.
	int caldataIndex(int ix, int iy, int iz) const;

	// Simulate a shower of a given energy, starting from the impact point (x,y)
	// of the electron at the front end of the calorimeter.
	// TODO: to be implemented.
	void SimulateShower(float x, float y, float energy);

	//Simulate a hadronic shower
	void SimulateHadShower(float x, float y, float energy, float f);

	// Print all the cells.
	friend ostream& operator<<(ostream& os, const CaloSimulation& cs);

private:

   vector<CaloCell> m_caldata;
};

#endif
