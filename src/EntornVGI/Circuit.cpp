#include "stdafx.h"
#include "Circuit.h"

void Circuit::m_GenRoadTexture()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_roadImg[i][j][0] = 255;
			m_roadImg[i][j][1] = 0;
			m_roadImg[i][j][2] = 255;
			m_roadImg[i][j][3] = 255;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 3; j < 5; j++)
		{
			m_roadImg[i][j][0] = 255;
			m_roadImg[i][j][1] = 255;
			m_roadImg[i][j][2] = 255;
			m_roadImg[i][j][3] = 255;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 5; j < 8; j++)
		{
			m_roadImg[i][j][0] = 255;
			m_roadImg[i][j][1] = 0;
			m_roadImg[i][j][2] = 255;
			m_roadImg[i][j][3] = 255;
		}
	}

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &m_roadTextureId);
	//m_roadTextureId--; // PC_Q_TXTID
	//glActiveTexture(m_roadTextureId);
	glBindTexture(GL_TEXTURE_2D, m_roadTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_roadImg);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D);
}

Circuit::~Circuit()
{

}

void Circuit::Init()
{
	m_GenRoadTexture();
}

Vector3 Circuit::CalcPosition(float f)
{
	return m_spline.CalcPosition(f);
}

Vector3 Circuit::CalcDirection(float f)
{
	return m_spline.CalcDirection(f);
}

void Circuit::CalcDirPos(float f, Vector3 & direction, Vector3 & position)
{
	m_spline.CalcDirPos(f, direction, position);
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

	//m_spline.Debug(true, CircuitsResolutions[(int)m_index]);

	glBindTexture(GL_TEXTURE_2D, m_roadTextureId);
	glBegin(GL_QUAD_STRIP);

	float f = 0;

	Vector3 p = m_spline.CalcPosition(f);
	Vector3 d = m_spline.CalcDirection(f);
	d.Normalize();

	Vector3 perp = d.DirCrossP(Vector3(0, 1, 0));
	Vector3 pl = p + (perp * (-width));
	Vector3 pr = p + (perp * width);

	glTexCoord2f(0.0, 0.0); glVertex3f(pl.X(), pl.Y(), pl.Z());
	glTexCoord2f(1.0 * m_carrils, 0.0); glVertex3f(pr.X(), pr.Y(), pr.Z());

	for (f = inc; f < 1; f += inc)
	{
		p = m_spline.CalcPosition(f);
		d = m_spline.CalcDirection(f);
		d.Normalize();

		perp = d.DirCrossP(Vector3(0, 1, 0));
		pl = p + (perp * (-width));
		pr = p + (perp * width);

		glTexCoord2f(0.0, 1.0); glVertex3f(pl.X(), pl.Y(), pl.Z());
		glTexCoord2f(1.0 * m_carrils, 1.0); glVertex3f(pr.X(), pr.Y(), pr.Z());
		glTexCoord2f(0.0, 0.0); glVertex3f(pl.X(), pl.Y(), pl.Z());
		glTexCoord2f(1.0 * m_carrils, 0.0); glVertex3f(pr.X(), pr.Y(), pr.Z());
	}

	// Ultim vertex = posicio inicial
	p = m_spline.CalcPosition(0);
	d = m_spline.CalcDirection(0);
	d.Normalize();

	perp = d.DirCrossP(Vector3(0, 1, 0));
	pl = p + (perp * (-width));
	pr = p + (perp * width);

	glTexCoord2f(0.0, 1.0); glVertex3f(pl.X(), pl.Y(), pl.Z());
	glTexCoord2f(1.0 * m_carrils, 1.0); glVertex3f(pr.X(), pr.Y(), pr.Z());

	glEnd();
}
