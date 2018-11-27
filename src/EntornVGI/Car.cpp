#include "stdafx.h"
#include "Car.h"

void Car::SetWheel(int index, GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
	if (index >= 0 && index < m_wheelsLength)
	{
		m_wheels[index] = new MobileOGLObject(glIndex, position, rotation, scale);
		m_body.SetChild(index, m_wheels[index]);
	}
}

void Car::SetBody(GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
}

Car::~Car()
{
}
