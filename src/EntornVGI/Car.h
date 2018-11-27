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
	Car(GLuint bodyGlIndex, int wheelsLength, Vector3 bodyPosition, Vector3 bodyRotation, Vector3 bodyScale) : MobileOGLObject()
	{
		m_body = MobileOGLObject(bodyGlIndex, bodyPosition, bodyRotation, bodyScale);

		if (wheelsLength > 0)
		{
			m_wheelsLength = wheelsLength;
			m_body.SetChildsLength(wheelsLength);
			m_wheels = new MobileOGLObject*[m_wheelsLength+1];
		}
		else
		{
			m_wheelsLength = 0;
			m_wheels = NULL;
		}
	};
	void SetWheel(int index, GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	void SetBody(GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	//Car & Car::operator=(const Car & c);
	~Car();
};

