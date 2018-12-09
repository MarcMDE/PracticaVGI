#include "stdafx.h"
#include "Spline.h"


Vector3 Spline::m_CubicInterpolate(float mu, Vector3 cps[4]) const
{
	Vector3 a0, a1, a2, a3;
	float mu2 = mu * mu;


	// Cublic spline
	//a0 = (*cps[3]) - (*cps[2]) - cps[0] + (*cps[1]);
	//a1 = cps[0] - (*cps[1]) - a0;
	//a2 = (*cps[2]) - cps[0];
	//a3 = (*cps[1]);
	

	// Catmull-Roin cubic Splines
	a0 = (cps[0])*(-0.5) + (cps[1])*1.5 - (cps[2])* 1.5 + (cps[3])*0.5;
	a1 = (cps[0]) - (cps[1])*2.5 + (cps[2])*2 - (cps[3])*0.5;
	a2 = (cps[0])*(-0.5) + (cps[2])*0.5;
	a3 = (cps[1]);

	return (a0*mu*mu2 + a1 * mu2 + a2 * mu + a3);
}


Vector3 Spline::m_CubicInterpolateD(float mu, Vector3 cps[4]) const
{
	Vector3 a0, a1, a2, a3;
	float mu2 = mu * mu;

	// Cublic spline
	//a0 = (cps[3]) - (cps[2]) - cps[0] + (cps[1]);
	//a1 = cps[0] - (cps[1]) - a0;
	//a2 = (cps[2]) - cps[0];
	//a3 = (cps[1]);
	

	// Catmull-Roin cubic Splines
	a0 = (cps[0]) * (-0.5) + (cps[1]) * 1.5 - (cps[2]) * 1.5 + (cps[3]) * 0.5;
	a1 = (cps[0]) - (cps[1]) * 2.5 + (cps[2]) * 2 - (cps[3]) * 0.5;
	a2 = (cps[0]) * (-0.5) + (cps[2]) * 0.5;
	a3 = (cps[1]);

	// TODO: Retornar derivada
	return (a0*mu*mu2 + a1 * mu2 + a2 * mu + a3);
}


Vector3 Spline::m_BSpline(float mu, Vector3 cps[4]) const
{
	Vector3 p = Vector3().Zero();
	float coef[4];
	int i, j;

	//Polinomis que multipliquen els punts de control del patch
	for (i = 0; i < 4; i++)
	{
		coef[i] = 0;
		for (j = 0; j < 4; j++)
			coef[i] = coef[i] * mu + A[i][j];
	}

	//Càlcul de la Posició
	for (i = 0; i < 4; i++)
	{
		p += (cps[i]) * coef[i];
	}

	return p;
}

Vector3 Spline::m_BSplineD(float mu, Vector3 cps[4]) const
{
	Vector3 dp = Vector3().Zero();
	float coef[4];
	int i, j;

	//Polinomis que multipliquen els punts de control del patch
	for (i = 0; i < 4; i++)
	{
		coef[i] = 0;
		for (j = 0; j < 3; j++)
			coef[i] = coef[i] * mu + (3 - j)*A[i][j];
	}

	//Càlcul de la Derivada
	for (i = 0; i < 4; i++)
	{
		dp += (cps[i]) * coef[i];
	}

	return dp;
}

Spline::Spline()
{
	m_size = 0;
}

void Spline::Load(string fileName)
{
	if (m_size != 0) delete[] m_spline;
	if (m_size != 0) delete[] m_pointsDistance;

	ifstream file;
	file.open(fileName);
	//m_circular = true;

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

	m_distance = 0;

	m_pointsDistance[0] = 0;
	for (int i = 1; i < m_size; i++)
	{
		m_pointsDistance[i] = m_pointsDistance[i - 1] + m_spline[i - 1].Distance(m_spline[i]);
	}
	m_distance = m_pointsDistance[m_size - 1];
}

void Spline::Debug(bool cp, int res) const
{
	if (cp)
	{
		float cpRad = 3;
		glColor3f(5, 0.7, 1);
		// For each control point
		for (int i=0; i < m_size; i++)
		{
			glPushMatrix();
				glTranslatef(m_spline[i].X(), m_spline[i].Y(), m_spline[i].Z());
				glutSolidSphere(cpRad, 4, 4);
			glPopMatrix();
		}
		glColor3f(1, 1, 1);
	}

	float inc = 1.0f / res;

	//glEnable(GL_LINE_STIPPLE);
	glLineWidth(3.0);
	//glLineStipple(1, 0x0101);
	glColor3f(1, 0, 1);
	glBegin(GL_LINES);
		Vector3 v = CalcPosition(0);
		glVertex3f(v.X(), v.Y(), v.Z());
		for (float f=inc; f < 1; f+=inc)
		{
			v = CalcPosition(f);
			glVertex3f(v.X(), v.Y(), v.Z());
			glVertex3f(v.X(), v.Y(), v.Z());
		}
		v = CalcPosition(1);
		glVertex3f(v.X(), v.Y(), v.Z());
	glEnd();
	glColor3f(1, 1, 1);

	glLineWidth(1.0);
}

Spline::~Spline()
{
	delete[] m_spline;
	delete[] m_pointsDistance;
}

Vector3 Spline::CalcPosition(float p) const // (0-1)
{
	Vector3 cps[4];

	float partialDist = m_distance * p; // dist to p

	int leftIndex = m_size - 1;
	while (m_size > 0 && m_pointsDistance[leftIndex] > partialDist) leftIndex--;

	float partialPointDist = partialDist - m_pointsDistance[leftIndex]; // dist left point to p
	p = partialPointDist / (m_pointsDistance[leftIndex + 1] - m_pointsDistance[leftIndex]); // controlar cas ultim punt
	
	int nextIndex;

	cps[0] = m_spline[leftIndex];

	nextIndex = leftIndex + 1;
	if (nextIndex >= m_size)
	{
		cps[1] = m_spline[nextIndex - m_size + 1];
		//else m_cps[1] = &m_spline[leftIndex];
	}
	else cps[1] = m_spline[nextIndex];

	nextIndex = leftIndex + 2;
	if (nextIndex >= m_size)
	{
		cps[2] = m_spline[nextIndex - m_size + 1];
		//else m_cps[2] = &m_spline[leftIndex];
	}
	else cps[2] = m_spline[nextIndex];

	nextIndex = leftIndex + 3;
	if (nextIndex >= m_size)
	{
		cps[3] = m_spline[nextIndex - m_size + 1];
		//else m_cps[3] = &m_spline[leftIndex];
	}
	else cps[3] = m_spline[nextIndex];

	return m_BSpline(p, cps);
	//return m_CubicInterpolate(p, cps);

	/*
	switch (s)
	{
	case CUBIC:
		m_cps[1] = &m_spline[leftIndex];

		if (leftIndex - 1 <= m_size) m_cps[0] = &m_spline[leftIndex];
		else m_cps[0] = &m_spline[leftIndex - 1];

		if (leftIndex + 1 >= m_size) m_cps[2] = &m_spline[leftIndex];
		else m_cps[2] = &m_spline[leftIndex + 1];

		if (leftIndex + 2 >= m_size) m_cps[3] = &m_spline[leftIndex];
		else m_cps[3] = &m_spline[leftIndex + 2];

		return m_CubicInterpolate(p);
		break;
	case SPLINE:
		m_cps[0] = &m_spline[leftIndex];

		nextIndex = leftIndex + 1;
		if (nextIndex >= m_size)
		{
			if (m_circular) m_cps[1] = &m_spline[nextIndex-m_size];
			else m_cps[1] = &m_spline[leftIndex];
		}
		else m_cps[1] = &m_spline[nextIndex];

		nextIndex = leftIndex + 2;
		if (nextIndex >= m_size)
		{
			if (m_circular) m_cps[2] = &m_spline[nextIndex - m_size];
			else m_cps[2] = &m_spline[leftIndex];
		}
		else m_cps[2] = &m_spline[nextIndex];

		nextIndex = leftIndex + 3;
		if (nextIndex >= m_size)
		{
			if (m_circular) m_cps[3] = &m_spline[nextIndex - m_size];
			else m_cps[3] = &m_spline[leftIndex];
		}
		else m_cps[3] = &m_spline[nextIndex];

		return m_BSpline(p);
		break;
	default:
		return Vector3().Zero();
		break;
	}
	*/
}

Vector3 Spline::CalcDirection(float p) const
{
	Vector3 cps[4];

	float partialDist = m_distance * p; // dist to p

	int leftIndex = m_size - 1;
	while (m_size > 0 && m_pointsDistance[leftIndex] > partialDist) leftIndex--;

	float partialPointDist = partialDist - m_pointsDistance[leftIndex]; // dist left point to p
	p = partialPointDist / (m_pointsDistance[leftIndex + 1] - m_pointsDistance[leftIndex]); // controlar cas ultim punt

	int nextIndex;

	cps[0] = m_spline[leftIndex];

	nextIndex = leftIndex + 1;
	if (nextIndex >= m_size)
	{
		cps[1] = m_spline[nextIndex - m_size + 1];
		//else m_cps[1] = &m_spline[leftIndex];
	}
	else cps[1] = m_spline[nextIndex];

	nextIndex = leftIndex + 2;
	if (nextIndex >= m_size)
	{
		cps[2] = m_spline[nextIndex - m_size + 1];
		//else m_cps[2] = &m_spline[leftIndex];
	}
	else cps[2] = m_spline[nextIndex];

	nextIndex = leftIndex + 3;
	if (nextIndex >= m_size)
	{
		cps[3] = m_spline[nextIndex - m_size + 1];
		//else m_cps[3] = &m_spline[leftIndex];
	}
	else cps[3] = m_spline[nextIndex];

	return m_BSplineD(p, cps);
	//return m_CubicInterpolateD(p, cps);
}

void Spline::CalcDirPos(float p, Vector3 & dir, Vector3 & pos)
{
	Vector3 cps[4];

	float partialDist = m_distance * p; // dist to p

	int leftIndex = m_size - 1;
	while (m_size > 0 && m_pointsDistance[leftIndex] > partialDist) leftIndex--;

	float partialPointDist = partialDist - m_pointsDistance[leftIndex]; // dist left point to p
	p = partialPointDist / (m_pointsDistance[leftIndex + 1] - m_pointsDistance[leftIndex]); // controlar cas ultim punt

	int nextIndex;

	cps[0] = m_spline[leftIndex];

	nextIndex = leftIndex + 1;
	if (nextIndex >= m_size)
	{
		cps[1] = m_spline[nextIndex - m_size + 1];
		//else m_cps[1] = &m_spline[leftIndex];
	}
	else cps[1] = m_spline[nextIndex];

	nextIndex = leftIndex + 2;
	if (nextIndex >= m_size)
	{
		cps[2] = m_spline[nextIndex - m_size + 1];
		//else m_cps[2] = &m_spline[leftIndex];
	}
	else cps[2] = m_spline[nextIndex];

	nextIndex = leftIndex + 3;
	if (nextIndex >= m_size)
	{
		cps[3] = m_spline[nextIndex - m_size + 1];
		//else m_cps[3] = &m_spline[leftIndex];
	}
	else cps[3] = m_spline[nextIndex];

	dir = m_BSplineD(p, cps);
	pos = m_BSpline(p, cps);
}

/*
Vector3 Spline::GetDirection(float p)
{
	float partialDist = m_distance * p; // dist to p

	int leftIndex = m_size - 1;
	while (m_size > 0 && m_pointsDistance[leftIndex] > partialDist) leftIndex--;

	float partialPointDist = partialDist - m_pointsDistance[leftIndex]; // dist left point to p
	p = partialPointDist / (m_pointsDistance[leftIndex + 1] - m_pointsDistance[leftIndex]); // controlar cas ultim punt

	int nextIndex;

	switch (s)
	{
	case CUBIC:
		m_cps[1] = &m_spline[leftIndex];

		if (leftIndex - 1 <= m_size) m_cps[0] = &m_spline[leftIndex];
		else m_cps[0] = &m_spline[leftIndex - 1];

		if (leftIndex + 1 >= m_size) m_cps[2] = &m_spline[leftIndex];
		else m_cps[2] = &m_spline[leftIndex + 1];

		if (leftIndex + 2 >= m_size) m_cps[3] = &m_spline[leftIndex];
		else m_cps[3] = &m_spline[leftIndex + 2];

		return m_CubicInterpolateD(p);
		break;
	case SPLINE:
		m_cps[0] = &m_spline[leftIndex];

		nextIndex = leftIndex + 1;
		if (nextIndex >= m_size)
		{
			if (m_circular) m_cps[1] = &m_spline[nextIndex - m_size];
			else m_cps[1] = &m_spline[leftIndex];
		}
		else m_cps[1] = &m_spline[nextIndex];

		nextIndex = leftIndex + 2;
		if (nextIndex >= m_size)
		{
			if (m_circular) m_cps[2] = &m_spline[nextIndex - m_size];
			else m_cps[2] = &m_spline[leftIndex];
		}
		else m_cps[2] = &m_spline[nextIndex];

		nextIndex = leftIndex + 3;
		if (nextIndex >= m_size)
		{
			if (m_circular) m_cps[3] = &m_spline[nextIndex - m_size];
			else m_cps[3] = &m_spline[leftIndex];
		}
		else m_cps[3] = &m_spline[nextIndex];

		return m_BSplineD(p);
		break;
	default:
		return Vector3().Zero();
		break;
	}
}
*/