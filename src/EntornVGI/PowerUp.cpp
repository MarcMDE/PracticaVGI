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


PowerUp::~PowerUp()
{
}
