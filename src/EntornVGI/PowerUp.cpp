#include "stdafx.h"
#include "PowerUp.h"


PowerUp::PowerUp()
{
	tamany = tamanyMax;
	textura = TXT_BOOST;
}

//void PowerUp::Init(int textura)
//{
//	this->textura = textura;
//}

void PowerUp::Draw()
{
	glPushMatrix();
		glTranslatef(m_position.X(), m_position.Y(), m_position.Z());
		glRotatef(-90.0f, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, textura);
		glutSolidCube(tamany);
	glPopMatrix();
}

bool PowerUp::CheckColision(Vector3 p)
{
	Vector3 d = p - m_position;

	if (d.X() < tamany / 2 || d.Y() < tamany / 2 || d.Z() < tamany / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


PowerUp::~PowerUp()
{
}
