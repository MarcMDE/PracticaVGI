#include "stdafx.h"
#include "Car.h"


Car::Car()
{

}

Car::Car(GLuint bodyGlIndex, int wheelsLength, Vector3 bodyPosition, Vector3 bodyRotation, Vector3 bodyScale)
{
	m_body = DynamicOGLObject(bodyGlIndex, bodyPosition, bodyRotation, bodyScale);
	if (wheelsLength > 0)
	{
		m_wheelsLength = wheelsLength;
		m_body.SetChildsLength(wheelsLength);
		m_wheels = new DynamicOGLObject*[m_wheelsLength];
	}
	else
	{
		m_wheelsLength = 0;
		m_wheels = NULL;
	}
}

void Car::SetWheel(int index, GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
	if (index >= 0 && index < m_wheelsLength)
	{
		m_wheels[index] = new DynamicOGLObject(glIndex, position, rotation, scale);
		m_body.SetChild(index, m_wheels[index]);
	}
}

OGLObject * Car::GetBody() 
{
	return &m_body;
}

DynamicOGLObject * Car::GetDynamicBody()
{
	return &m_body;
}


Car::~Car()
{
}
