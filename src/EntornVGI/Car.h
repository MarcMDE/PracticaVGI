#pragma once

#include "MobileOGLObject.h"
#include "OGLObject.h"

class Car : public MobileOGLObject
{
private:
	const float m_friction = 0.0001;
	const float m_gravity = 0.003;
	const float m_boostSpeed = 0.005;

	OGLObject m_body;
	MobileOGLObject** m_wheels;
	int m_wheelsLength;

	Vector3 m_direction;
	float m_speed;
	float m_progress;

public:
	Car() : MobileOGLObject() {};
	void Init(int wheelsLength, Vector3 position, Vector3 rotation, Vector3 scale);
	void SetWheel(int index, GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	void SetBody(GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	void Move(Vector3 pos, Vector3 dir);
	Vector3 GetDirection() const;
	void Boost();
	float GetProgress() const;
	void ResetProgress();

	//Car & Car::operator=(const Car & c);
	~Car();
};

