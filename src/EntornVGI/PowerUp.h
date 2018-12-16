#pragma once
#include "MobileOGLObject.h"

class PowerUp : public MobileOGLObject
{
private:
	int textura;
	int tamany;
	const int tamanyMax = 10;
public:
	PowerUp();
	~PowerUp();

	void Init(int textura);
	void Draw();
	bool CheckColision(Vector3 p);
};

