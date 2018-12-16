#include "stdafx.h"
#include "PowerUp.h"


PowerUp::PowerUp()
{
	tamany = tamanyMax;
}

void PowerUp::Init(int textura)
{
	this->textura = textura;
}

void PowerUp::Draw()
{
	glBindTexture(GL_TEXTURE_2D, textura);
	glutSolidCube(tamany);
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
