#ifndef CaloCell_h
#define CaloCell_h

/**
 * CaloCell
 * Reprensents a cell of the calorimeter, and its energy.
 */

#include "CellAddress.h"

class CaloCell
{
public:

	// Default constructor needed of containers of the standard template library.
	CaloCell();

	// Full constructor.
	CaloCell(const CellAddress& ca, float energy);

	// Accessors.
	float energy() const;
	CellAddress address() const;

	// "Print" function.
	friend std::ostream& operator<<(std::ostream& os, const CaloCell& y)
	{
		os << "[" << y.address() << ", " << y.energy() << "]";
		return os;
	}

private:
	float m_energy;
	CellAddress m_address;

};

#endif
