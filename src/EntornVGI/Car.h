#pragma once

#include "MobileOGLObject.h"
#include "OGLObject.h"

class Car : MobileOGLObject
{
private:
	MobileOGLObject m_body;
	MobileOGLObject** m_wheels;
	int m_wheelsLength;

	Vector3 m_speed;
	Vector3 m_direction;
public:
	Car();
	Car(GLuint bodyGlIndex, int wheelsLength, Vector3 bodyPosition, Vector3 bodyRotation, Vector3 bodyScale);
	void SetWheel(int index, GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	OGLObject * GetBody();
	Car & Car::operator=(const Car & c);
	~Car();
};

