#pragma once


#include "MuonTomography.h"


class Material {
public:

	double X0;

	double row, col;


	Material(double r, double c, double x0) {
		row = r;
		col = c;
		X0 = x0;
	}

};
