#include "stdafx.h"
#include "Circuit.h"

Circuit::~Circuit()
{

}

void Circuit::Load(Circuits c)
{
	m_index = c;
	m_spline.Load(CircuitsFileNames[(int)m_index]);
}

void Circuit::Draw() const
{
	float inc = 1.0f / CircuitsResolutions[(int)m_index];
	int width = CarrilWidth * m_carrils;

	//m_spline.Debug(true, CircuitsResolutions[(int)m_index]);

	glBegin(GL_QUAD_STRIP);
	for (float f = 0.0f; f < 1; f += inc)
	{
		Vector3 p = m_spline.CalcPosition(f);
		Vector3 d = m_spline.CalcDirection(f);
		d.Normalize();

		Vector3 perp = d.DirCrossP(Vector3(0, 1, 0));
		Vector3 pl = p + (perp * (-width));
		Vector3 pr = p + (perp * width);

		glVertex3f(pl.X(), pl.Y(), pl.Z());
		glVertex3f(pr.X(), pr.Y(), pr.Z());
	}

	// Ultim vertex = posicio inicial
	Vector3 p = m_spline.CalcPosition(0);
	Vector3 d = m_spline.CalcDirection(0);
	d.Normalize();

	Vector3 perp = d.DirCrossP(Vector3(0, 1, 0));
	Vector3 pl = p + (perp * (-width));
	Vector3 pr = p + (perp * width);

	glVertex3f(pl.X(), pl.Y(), pl.Z());
	glVertex3f(pr.X(), pr.Y(), pr.Z());

	glEnd();
}
