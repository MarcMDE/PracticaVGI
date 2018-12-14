#pragma once
#include "OGLObject.h"

class SkyBox : public OGLObject
{
private:
	int s;
	int textura;
public:

	// Circuit() : m_carrils(3), OGLObject() {};
	SkyBox();
	SkyBox(int s, int textura) : s(s), textura(textura) {};
	~SkyBox();
	void Draw();
};

