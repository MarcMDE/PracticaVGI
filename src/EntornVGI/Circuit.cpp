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

void Circuit::UnsetPowerUps()
{
	m_poweUpsLength = -1;
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

void Circuit::UpdatePowerUps()
{
	if (m_poweUpsLength > 0)
	{
		for (int i = 0; i < m_carrils; i++)
		{
			for (int j = 0; j < m_poweUpsLength; j++)
			{
				m_powerUps[i][j].Rotate(Vector3(1.5f, 0, 0));
			}
		}
	}
}

void Circuit::Load(Circuits c)
{
	m_index = c;
	m_spline.Load(CircuitsFileNames[(int)m_index]);
	m_torusXrotation = CalcDirection(0).GetAngles().X();
}

float Circuit::getDistance()
{
	
	return m_spline.getdistance();

}

void Circuit::LoadPowerUps()
{

	if (m_poweUpsLength != 0 && m_powerUps != NULL)
	{
		for (int i = 0; i < m_carrilsPowerUps; i++)
		{
			delete[] m_powerUps[i];
		}

		delete[] m_powerUps;
	}

	m_carrilsPowerUps = m_carrils;

	float f;
	string fileName = CircuitsPwFileNames[m_index];

	m_powerUps = new PowerUp* [m_carrils];

	ifstream file;
	file.open(fileName);
	//m_circular = true;

	if (file.is_open())
	{
		file >> m_poweUpsLength;

		for (int i = 0; i < m_carrils; i++)
		{
			m_powerUps[i] = new PowerUp[m_poweUpsLength];
		}

		int i = 0;

		Vector3 pwPos;
		Vector3 dir;
		while (!file.eof())
		{
			file >> f;
			for (int j = 0; j < m_carrils; j++)
			{
				CalcDirPos(f, j, dir, pwPos);
				pwPos = pwPos + Vector3(0, PowerUpOffsetY, 0);
				m_powerUps[j][i].SetPosition(pwPos);
			}

			i++;
		}

		file.close();
	}
}

bool Circuit::GetPUColission(Vector3 pos, int c)
{

	for (int i = 0; i < m_poweUpsLength; i++) {

		if (m_powerUps[c][i].CheckColision(pos + Vector3(0, PowerUpOffsetY, 0))) {

			return true;

		}

	}

	return false;
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


	glDisable(GL_TEXTURE_2D);

	float colorG = 1.0f;
	glColor3f(1.0f - colorG, colorG, 1.0f - colorG);
	// Dibuix boletes
	inc = 1.0f / BoletesMax;
	bool rightBoleta = true;
	for (f = inc; f < 1; f += inc)
	{
		m_spline.CalcDirPos(f, d, p);
		d.Normalize();

		perp = d.DirCrossP(Vector3(0, 1, 0));
		pl = p + (perp * (-width-BoletesOffsetX));
		pr = p + (perp * (width+BoletesOffsetX));

			glColor3f(1.0f - colorG, colorG, 1.0f - colorG);

			if (rightBoleta)
			{
				// Dibuixem boleta dreta
				glPushMatrix();
				glTranslatef(pr.X(), pr.Y() + BoletesOffsetY, pr.Z());
				glutSolidSphere(BoletesRad, 10, 10);
				glPopMatrix();
			}
			else
			{
				// Dibuixem boleta esquerra
				glPushMatrix();
				glTranslatef(pl.X(), pl.Y() + BoletesOffsetY, pl.Z());
				glutSolidSphere(BoletesRad, 10, 10);
				glPopMatrix();
			}

			rightBoleta = !rightBoleta;

			colorG -= inc;
			//glColor3f(1, 1, 1);
	}


	glBegin(GL_LINES);

	glLineWidth(4.0f);

	// Barrera esqerra
	colorG = 1.0f;
	glColor3f(1.0f - colorG, colorG, 1.0f - colorG);
	f = 0;
	m_spline.CalcDirPos(f, d, p);
	d.Normalize();

	perp = d.DirCrossP(Vector3(0, 1, 0));
	pl = p + (perp * (-width - BoletesOffsetX));

	glVertex3f(pl.X(), pl.Y() + BoletesOffsetY, pl.Z());

	for (f = f+inc; f < 1-inc; f += inc)
	{
		glColor3f(1.0f - colorG, colorG, 1.0f - colorG);
		m_spline.CalcDirPos(f, d, p);
		d.Normalize();

		perp = d.DirCrossP(Vector3(0, 1, 0));
		pl = p + (perp * (-width - BoletesOffsetX));

		glVertex3f(pl.X(), pl.Y() + BoletesOffsetY, pl.Z());
		glVertex3f(pl.X(), pl.Y() + BoletesOffsetY, pl.Z());
		colorG -= inc;
	}

	m_spline.CalcDirPos(1, d, p);
	d.Normalize();

	perp = d.DirCrossP(Vector3(0, 1, 0));
	pl = p + (perp * (-width - BoletesOffsetX));

	glVertex3f(pl.X(), pl.Y() + BoletesOffsetY, pl.Z());


	// Barrera dreta
	colorG = 1.0f;
	glColor3f(1.0f - colorG, colorG, 1.0f - colorG);
	f = 0;
	m_spline.CalcDirPos(f, d, p);
	d.Normalize();

	perp = d.DirCrossP(Vector3(0, 1, 0));
	pr = p + (perp * (width + BoletesOffsetX));

	glVertex3f(pr.X(), pr.Y() + BoletesOffsetY, pr.Z());

	for (f = f + inc; f < 1; f += inc)
	{
		glColor3f(1.0f - colorG, colorG, 1.0f - colorG);
		m_spline.CalcDirPos(f, d, p);
		d.Normalize();

		perp = d.DirCrossP(Vector3(0, 1, 0));
		pr = p + (perp * (width + BoletesOffsetX));

		glVertex3f(pr.X(), pr.Y() + BoletesOffsetY, pr.Z());
		glVertex3f(pr.X(), pr.Y() + BoletesOffsetY, pr.Z());
		colorG -= inc;
	}

	m_spline.CalcDirPos(1, d, p);
	d.Normalize();

	perp = d.DirCrossP(Vector3(0, 1, 0));
	pr = p + (perp * (width + BoletesOffsetX));

	glVertex3f(pr.X(), pr.Y() + BoletesOffsetY, pr.Z());


	glEnd();


	glColor3f(1, 1, 1);

   
   
	glEnable(GL_TEXTURE_2D);

	if (m_poweUpsLength > 0)
	{
		for (int i = 0; i < m_carrils; i++)
		{
			for (int j = 0; j < m_poweUpsLength; j++)
			{
				m_powerUps[i][j].Draw();
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glColor3f(0.7f, 0.2f, 1);
	Vector3 pos = CalcPosition(0);
	glPushMatrix();
	glTranslatef(pos.X(), pos.Y(), pos.Z());
	glRotatef(m_torusXrotation * RAD_TO_DEG + 90.0f, 0, 1, 0);
	glutSolidTorus(20, (m_carrils*CarrilWidth) + 30, 20, 20);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
