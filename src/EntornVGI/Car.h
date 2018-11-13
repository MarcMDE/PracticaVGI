#pragma once

#include "DynamicOGLObject.h"

class Car
{
private:
	DynamicOGLObject m_body;
	DynamicOGLObject** m_wheels;
	int m_wheelsLength;

	Vector3 m_speed;
	Vector3 m_direction;
public:
	Car();
	Car(GLuint bodyGlIndex, int wheelsLength, Vector3 bodyPosition, Vector3 bodyRotation, Vector3 bodyScale);
	void SetWheel(int index, GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	OGLObject * GetBody();
	~Car();
};

