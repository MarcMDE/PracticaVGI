#pragma once

#include "MobileOGLObject.h"
#include "OGLObject.h"

class Car : public MobileOGLObject
{
private:
	OGLObject m_body;
	MobileOGLObject** m_wheels;
	int m_wheelsLength;

	Vector3 m_speed;
public:
	Car() : MobileOGLObject() {};
	Car(int wheelsLength, Vector3 position, Vector3 rotation, Vector3 scale) : MobileOGLObject()
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;

		if (wheelsLength > 0)
		{
			m_wheelsLength = wheelsLength;
			m_wheels = new MobileOGLObject*[m_wheelsLength+1];
			SetChildsLength(wheelsLength + 1); // X rodes, 1 carroceria, 1 camara
		}
		else
		{
			m_wheelsLength = 0;
			m_wheels = NULL;
		}
	};
	void SetWheel(int index, GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	void SetBody(GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	//Car & Car::operator=(const Car & c);
	~Car();
};

