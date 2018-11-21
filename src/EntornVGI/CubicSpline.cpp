#include "stdafx.h"
#include "CubicSpline.h"


Vector3 CubicSpline::CubicInterpolate(Vector3 y0, Vector3 y1, Vector3 y2, Vector3 y3, double mu)
{
	Vector3 a0, a1, a2, a3;
	double mu2;

	mu2 = mu * mu;
	a0 = y3 - y2 - y0 + y1;
	a1 = y0 - y1 - a0;
	a2 = y2 - y0;
	a3 = y1;

	return (a0*mu*mu2 + a1 * mu2 + a2 * mu + a3);
}

CubicSpline::CubicSpline()
{
}

CubicSpline::CubicSpline(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (file.is_open())
	{
		file >> size;
		spline = new Vector3[size];

		int i = 0;

		while (file.eof())
		{
			float x, y, z;
			file >> x >> y >> z;
			spline[i] = Vector3(x, y, z);
			i++;
		}

		file.close();
	}

	distance = spline[0].Distance(spline[size - 1]);

	for (int i = 0; i < size; i++)
	{
		pointsDistance[i] = spline[0].Distance(spline[i]);
	}
}


CubicSpline::~CubicSpline()
{
}

Vector3 CubicSpline::GetPosition(float p)
{
	int leftIndex = (size - 1) * p;
	float partialDist = distance * p;
	float partialPointDist = partialDist - pointsDistance[leftIndex];
	p = partialPointDist / (pointsDistance[leftIndex + 1] - pointsDistance[leftIndex]);

	Vector3 v0, v2, v3;

	if (leftIndex - 1 < 0) v0 = spline[leftIndex];
	else v0 = spline[leftIndex - 1];

	if (leftIndex + 1 >= size) v2 = spline[leftIndex];
	else v2 = spline[leftIndex + 1];

	if (leftIndex + 2 >= size) v2 = spline[leftIndex];
	else v2 = spline[leftIndex + 2];

	return CubicInterpolate(v0, spline[leftIndex], v2, v3, p);
}
