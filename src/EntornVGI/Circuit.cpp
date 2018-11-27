#include "stdafx.h"
#include "Circuit.h"


Circuit::Circuit()
{
	m_carrils = 1;
}


Circuit::Circuit(int carrils)
{
	m_carrils = carrils;
}

Circuit::~Circuit()
{

}

void Circuit::Load(Circuits c)
{
	m_index = c;
	m_spline.Load(CircuitsFileNames[(int)m_index]);
}

void Circuit::Draw()
{
	float inc = 1.0f / CircuitsResolutions[(int)m_index];
	int width = CarrilWidth * m_carrils;

	glBegin(GL_QUAD_STRIP);
	for (float f = 0.0f; f < 1; f += inc)
	{
		Vector3 p = m_spline.GetPosition(f);
		Vector3 d = m_spline.GetDirection(f);
		d.Normalize();

		Vector3 perp = d.DirCrossP(Vector3(0, 1, 0));
		Vector3 pl = p + (perp * (-width));
		Vector3 pr = p + (perp * width);

		glVertex3f(pl.X(), pl.Y(), pl.Z());
		glVertex3f(pr.X(), pr.Y(), pr.Z());
	}

	// Ultim vertex = posicio inicial
	Vector3 p = m_spline.GetPosition(0);
	Vector3 d = m_spline.GetDirection(0);
	d.Normalize();

	Vector3 perp = d.DirCrossP(Vector3(0, 1, 0));
	Vector3 pl = p + (perp * (-width));
	Vector3 pr = p + (perp * width);

	glVertex3f(pl.X(), pl.Y(), pl.Z());
	glVertex3f(pr.X(), pr.Y(), pr.Z());

	glEnd();
}
