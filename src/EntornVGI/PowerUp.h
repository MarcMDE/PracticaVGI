#pragma once
#include "OGLObject.h"

class PowerUp : public OGLObject
{
private:
	int textura;
	int tamany;
	const int tamanyMax = 10;
public:
	PowerUp();
	void Init(int textura);
	~PowerUp();
};

