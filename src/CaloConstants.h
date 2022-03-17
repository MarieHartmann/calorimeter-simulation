#ifndef CaloConstants_h
#define CaloConstants_h

/**
 * CaloConstants
 * Defines constants used across many files of the project.
 */

namespace CalConst {
	// Dimensions, in meters.
	static const float ZMin = 0.;
	static const float ZMax = 1.;
	static const float XYMin = -2.;
	static const float XYMax = 2.;

	static const int NbCellsInXY = 40;
	static const int NbLayers = 1;

	// Cell size in x-y.
	static const float XYSize = (XYMax - XYMin) / NbCellsInXY;
	static const float ZSize = (ZMax - ZMin) / NbLayers;

	// Parameters of shower development
	static const float MR = 0.05; // Moliere Radius in meters
	static const float X0 = 0.01; // Radiation Length in meters
	static const float a = 4.;
	static const float b = 0.5;
	static const float E0 = 50; // Energy in GeV
}

#endif
