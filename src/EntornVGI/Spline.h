#pragma once
#include "Vector3.h"
#include <iostream>
#include <fstream>

using namespace std;

//enum SPLINE_TYPES{CUBIC=0, SPLINE=1};

class Spline
{

private:
	//Matriu dels Splines
	const double A[4][4] =
	{
		{-1.0 / 6.0,   0.5,  -0.5,  1.0 / 6.0 },
		{   0.5, -1.0,   0.0,  4.0 / 6.0 },
		{  -0.5,  0.5,   0.5,  1.0 / 6.0 },
		{ 1.0 / 6.0,   0.0,   0.0,    0.0   }
	};

	Vector3 *m_spline;
	int m_size;
	float m_distance;
	float *m_pointsDistance;
	//bool m_circular;
	//Vector3 m_CubicInterpolate(float mu);
	//Vector3 m_CubicInterpolateD(float mu);
	Vector3 m_BSpline(float mu, Vector3 cps[4]) const;
	Vector3 m_BSplineD(float mu, Vector3 cps[4]) const;

public:
	Spline();
	void Load(string fileName);
	void Debug(bool cp, int res) const;
	~Spline();
	
	Vector3 CalcPosition(float p) const;
	Vector3 CalcDirection(float p) const;
};

