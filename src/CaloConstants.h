#ifndef CaloConstants_h
#define CaloConstants_h

/**
 * CaloConstants
 * Defines constants used across many files of the project.
 */

namespace CalConst {
	// Dimensions, in meters.
	static const float ZMin = 0.;
	static const float ZMax = 100.;
	static const float XYMin = -200.;
	static const float XYMax = 200.;

	static const int NbCellsInXY = 40;
	static const int NbLayers = 30;

	// Cell size in x-y.
	static const float XYSize = (XYMax - XYMin) / NbCellsInXY;
	static const float ZSize = (ZMax - ZMin) / NbLayers;

	// Electronic shower parametrization.
	static const float EM_Rm = 5.; // Molière radius
	static const float EM_a = 4;
	static const float EM_b = 0.5;
	static const float EM_Gamma_a = 6;
	static const float X0 = 1.; // radiation length (in cm)

	// Purely hadronic shower parametrization/
	static const float HA_Rm = 10.; // Molière radius
	static const float HA_a = 2;
	static const float HA_b = 1;
	static const float HA_Gamma_a = 1;
	static const float L = 10.; // Hadronic length (in cm)

}

#endif
