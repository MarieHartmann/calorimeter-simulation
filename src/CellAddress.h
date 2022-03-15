#ifndef CellAddress_h
#define CellAddress_h

/**
 * CellAddress
 * Implements is a way to identify a calorimter cell using its positions along
 * the x, y and z axis.
 */

#include <iostream>

class CellAddress
{
public:
	// Default constructor, gives you an invalid address.
	CellAddress();

	// Full constructor.
	CellAddress(int ix, int iy, int layer);

	// Is the address valid.
	bool IsValid() const;

	// Accessors.
	int ix() const;
	int iy() const;
	int layer() const;

	// This defines comparator between two CellAddress. This is necessary for
	// some container types of the standard template library (std).
	bool operator<(const CellAddress& x) const
	{
		if (x.m_iy == this ->m_iy && x.m_ix == this->m_ix) return (this->m_layer < x.m_layer);
		if (x.m_ix == this->m_ix) return (this->m_iy < x.m_iy);
		return (this->m_ix < x.m_ix);
	}

	bool operator>(const CellAddress& x) const
	{
		if (x.m_iy == this ->m_iy && x.m_ix == this->m_ix) return (this->m_layer > x.m_layer);
		if (x.m_ix == this->m_ix) return (this->m_iy > x.m_iy);
		return (this->m_ix > x.m_ix);
	}

	// Display cell address content.
	friend std::ostream& operator<<(std::ostream& os, const CellAddress& y)
	{
		os << "(" << y.ix() << ", " << y.iy() << ", " << y.layer() << ")";
		return os;
	}

private:
	int m_ix;
	int m_iy;
	int m_layer;

};

#endif
