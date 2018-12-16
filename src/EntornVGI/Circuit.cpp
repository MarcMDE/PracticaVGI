#include "stdafx.h"
#include "Circuit.h"

void Circuit::m_GenRoadTexture()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_roadImg[i][j][0] = 0;
			m_roadImg[i][j][1] = 0;
			m_roadImg[i][j][2] = 0;
			m_roadImg[i][j][3] = 255;
		}
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 7; j < 9; j++)
		{
			m_roadImg[i][j][0] = 255;
			m_roadImg[i][j][1] = 255;
			m_roadImg[i][j][2] = 255;
			m_roadImg[i][j][3] = 255;
		}
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 9; j < 16; j++)
		{
			m_roadImg[i][j][0] = 0;
			m_roadImg[i][j][1] = 0;
			m_roadImg[i][j][2] = 0;
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

void Circuit::Init(int carrils)
{
	m_carrils = carrils;
	m_GenRoadTexture();
}

Vector3 Circuit::CalcPosition(float f)
{
	return m_spline.CalcPosition(f);
}

Vector3 Circuit::CalcDirection(float f)
{
	return m_spline.CalcDirection(f);

	/*Vector3 posF = m_spline.CalcPosition(f);

	if (f + 0.001 < 1) f += 0.001;
	else f = 0;

	Vector3 posN = m_spline.CalcPosition(f);

	return (posN - posF);*/
}

void Circuit::CalcDirPos(float f, int c, Vector3 & direction, Vector3 & position)
{
	m_spline.CalcDirPos(f, direction, position);
	//direction = CalcDirection(f);

	direction.Normalize();
	Vector3 perp = direction.DirCrossP(Vector3(0, 1, 0));

	//if (m_carrils > 1)
	{
		position = position - perp * (CarrilWidth * m_carrils / 2);
		
		position += perp * CarrilWidth/2;
		
		int i = 0;
		while (i < c)
		{
			position += perp * CarrilWidth;
			i++;
		}
	}
}

Circuits Circuit::GetCurrCircuit()
{
	return m_index;
}

void Circuit::SetCarrils(int c)
{
	m_carrils = c;
}

void Circuit::Load(Circuits c)
{
	m_index = c;
	m_spline.Load(CircuitsFileNames[(int)m_index]);
}

float Circuit::getDistance()
{
	
	return m_spline.getdistance();

}

void Circuit::LoadPowerUps(Circuits c)
{
	string nom = CircuitsPwFileNames[c];


	m_carrils; //llegir numero arxiu
}

void Circuit::Draw()
{
	float inc = 1.0f / CircuitsResolutions[(int)m_index];
	int width = CarrilWidth * m_carrils / 2;

	//m_spline.Debug(true, CircuitsResolutions[(int)m_index]);

	glBindTexture(GL_TEXTURE_2D, m_roadTextureId);
	glBegin(GL_QUAD_STRIP);

	float f = 0;

	Vector3 p; //= m_spline.CalcPosition(f);
	Vector3 d; // = m_spline.CalcDirection(f);
	m_spline.CalcDirPos(f, d, p);
	d.Normalize();

	Vector3 perp = d.DirCrossP(Vector3(0, 1, 0));
	Vector3 pl = p + (perp * (-width));
	Vector3 pr = p + (perp * width);

	glTexCoord2f(0.0, 0.0); glVertex3f(pl.X(), pl.Y(), pl.Z());
	glTexCoord2f(1.0 * m_carrils, 0.0); glVertex3f(pr.X(), pr.Y(), pr.Z());

	for (f = inc; f < 1; f += inc)
	{
		//p = m_spline.CalcPosition(f);
		//d = m_spline.CalcDirection(f);
		m_spline.CalcDirPos(f, d, p);
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
	//p = m_spline.CalcPosition(0);
	//d = m_spline.CalcDirection(0);
	m_spline.CalcDirPos(0, d, p);
	d.Normalize();

	perp = d.DirCrossP(Vector3(0, 1, 0));
	pl = p + (perp * (-width));
	pr = p + (perp * width);

	glTexCoord2f(0.0, 1.0); glVertex3f(pl.X(), pl.Y(), pl.Z());
	glTexCoord2f(1.0 * m_carrils, 1.0); glVertex3f(pr.X(), pr.Y(), pr.Z());

	glEnd();
}
