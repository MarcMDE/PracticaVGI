#pragma once

#include "MobileOGLObject.h"
#include "OGLObject.h"

class Car : public MobileOGLObject
{
private:
	const float m_friction = 0.001;
	const float m_gravity = 0.003;
	const float m_boostSpeed = 0.05;

	OGLObject m_body;
	MobileOGLObject** m_wheels;
	int m_wheelsLength;

	Vector3 m_direction;
	float m_speed;
	float m_progress;

public:
	Car() : MobileOGLObject() {};
	Car(int wheelsLength, Vector3 position, Vector3 rotation, Vector3 scale) : MobileOGLObject()
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;

		m_direction = Vector3().Zero();
		m_speed = 0;
		m_progress = 0;

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
	void Move(Vector3 pos, Vector3 dir);
	//Vector3 GetDirection() const;
	void Boost();

	//Car & Car::operator=(const Car & c);
	~Car();
};

