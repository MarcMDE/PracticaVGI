#pragma once
#include "Vector3.h"
#include <iostream>
#include <fstream>

using namespace std;


class CubicSpline
{
private:
	Vector3 *spline;
	int size;
	float distance;
	float *pointsDistance;
	Vector3 CubicInterpolate(Vector3 y0, Vector3 y1, Vector3 y2, Vector3 y3, double mu);

public:
	CubicSpline();
	CubicSpline(string fileName);
	~CubicSpline();
	
	Vector3 GetPosition(float p);
};

