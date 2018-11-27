#include "stdafx.h"
#include "Car.h"

void Car::SetWheel(int index, GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
	if (index >= 0 && index < m_wheelsLength)
	{
		m_wheels[index] = new MobileOGLObject(glIndex, position, rotation, scale);
		SetChild(index + 1, m_wheels[index]);
	}
}

void Car::SetBody(GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
	m_body = MobileOGLObject(glIndex, position, rotation, scale);
	SetChild(0, &m_body);
}

Car::~Car()
{
	delete[] m_wheels;
}
