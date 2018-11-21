#include "stdafx.h"
#include "CubicSpline.h"


Vector3 CubicSpline::m_CubicInterpolate(Vector3 y0, Vector3 y1, Vector3 y2, Vector3 y3, double mu)
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

int CubicSpline::m_GetNextIndex(int i)
{
	if (i < m_size - 1) i++;
	else if (m_circular) i = 0;
	
	return i;
}

CubicSpline::CubicSpline()
{
}

CubicSpline::CubicSpline(string fileName)
{
	ifstream file;
	file.open(fileName);

	m_circular = false;

	if (file.is_open())
	{
		file >> m_size;
		m_spline = new Vector3[m_size];
		m_pointsDistance = new float[m_size];

		int i = 0;

		while (!file.eof())
		{
			float x, y, z;
			file >> x >> y >> z;
			m_spline[i] = Vector3(x, y, z);
			i++;
		}

		file.close();
	}

	m_distance = m_spline[0].Distance(m_spline[m_size - 1]);

	for (int i = 0; i < m_size; i++)
	{
		m_pointsDistance[i] = m_spline[0].Distance(m_spline[i]);
	}
}

void CubicSpline::Draw(bool cp, int res)
{
	if (cp)
	{
		// For each control point
		for (int i=0; i < m_size; i++)
		{
			glPushMatrix();
				glTranslatef(m_spline[i].X(), m_spline[i].Y(), m_spline[i].Z());
				glutSolidSphere(3.0f, 8, 8);
			glPopMatrix();
		}

		float inc = 1.0f / res;

		//glEnable(GL_LINE_STIPPLE);
		glLineWidth(5.0);
		//glLineStipple(1, 0x0101);
		glBegin(GL_LINES);
		for (float f=0.0f; f < 1; f+=inc)
		{
			Vector3 v = GetPosition(f);
			glVertex3f(v.X(), v.Y(), v.Z());
		}
		glEnd();

		glLineWidth(1.0);
	}
}


CubicSpline::~CubicSpline()
{
	delete[] m_spline;
}


Vector3 CubicSpline::GetPosition(float p) // (0-1)
{
	
	int leftIndex = (m_size - 1) * p;

	int nextIndex;
	float partialDist = m_distance * p; // dist to p
	float partialPointDist = partialDist - m_pointsDistance[leftIndex]; // dist left point to p
	p = partialPointDist / (m_pointsDistance[leftIndex + 1] - m_pointsDistance[leftIndex]); // controlar cas ultim punt

	Vector3 v0, v2, v3;

	if (leftIndex - 1 <= m_size) v0 = m_spline[leftIndex];
	else v0 = m_spline[leftIndex - 1];

	if (leftIndex + 1 >= m_size) v2 = m_spline[leftIndex];
	else v2 = m_spline[leftIndex + 1];

	if (leftIndex + 2 >= m_size) v3 = m_spline[leftIndex];
	else v3 = m_spline[leftIndex + 2];
	return m_CubicInterpolate(v0, m_spline[leftIndex], v2, v3, p);
}
