#pragma once
#include "Vector3.h"
#include <iostream>

using namespace std;


class CubicSpline
{
private:
	Vector3 *spline;
	double CubicInterpolate(double y0, double y1, double y2, double y3, double mu);

public:
	CubicSpline();
	CubicSpline(string file);
	~CubicSpline();
};

