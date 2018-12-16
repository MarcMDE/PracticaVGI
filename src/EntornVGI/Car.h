#pragma once

#include "MobileOGLObject.h"
#include "OGLObject.h"

class Car : public MobileOGLObject
{
private:
	const int m_maxBoosts = 3;
	const int m_initialBoosts = m_maxBoosts;
	const float m_frictionC = 0.03f;
	const float m_gravityC = 0.06f;
	const int m_boostSpeedC = 10;
	const float m_brakeSpeedC = 2.5f;

	float m_friction;
	float m_gravity;
	float m_boostSpeed;
	float m_brakeSpeed;

	OGLObject m_body;
	MobileOGLObject** m_wheels;
	int m_wheelsLength;

	Vector3 m_direction;
	float m_speed;
	float m_progress;
	int m_boosts;
	int m_laps;

public:
	Car() : MobileOGLObject() {};
	void Init(int wheelsLength, Vector3 position, Vector3 rotation, Vector3 scale);
	void SetMoveValues(float dist);
	void SetWheel(int index, GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	void SetBody(GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	void Move(Vector3 pos, Vector3 dir);
	Vector3 GetDirection() const;
	void Boost();
	void Brake();
	float GetProgress() const;
	void ResetProgress();
	void AddBoost();

	int getLaps();

	//Car & Car::operator=(const Car & c);
	~Car();
};

