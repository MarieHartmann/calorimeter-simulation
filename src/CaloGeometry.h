#ifndef CaloGeometry_h
#define CaloGeometry_h

/**
 * CaloGeometry
 * Helpers to describe the geometry of the detector.
 */

class CellAddress; // Forward declaration, similar to #include.

class CaloGeometry
{
public:

	// Return false if the (x,y,z) point is not located in the calorimeter
	// volume otherwise return true and fill the CellAddress variables with the
	// address of the cell that contains this point.
	static bool IsInside(double xyz[3], CellAddress& cellAddress);

	// Give the position of the cell center.
	static double xCentre(const CellAddress& cellAddress);
	static double yCentre(const CellAddress& cellAddress);

private:

};

#endif
