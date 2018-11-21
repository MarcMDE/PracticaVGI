#pragma once
#include "Vector3.h"
#include <iostream>
#include <fstream>

using namespace std;


class CubicSpline
{
private:
	Vector3 *m_spline;
	int m_size;
	float m_distance;
	float *m_pointsDistance;
	bool m_circular;
	Vector3 m_CubicInterpolate(Vector3 y0, Vector3 y1, Vector3 y2, Vector3 y3, double mu);
	int m_GetNextIndex(int i);

public:
	CubicSpline();
	CubicSpline(string fileName);
	void Draw(bool cp, int res);
	~CubicSpline();
	
	Vector3 GetPosition(float p);
};

