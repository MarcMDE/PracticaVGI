#include "stdafx.h"
#include "Car.h"

void Car::Init(int wheelsLength, Vector3 position, Vector3 rotation, Vector3 scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	m_laps = 0;
	m_GetPU = 0;

	m_direction = Vector3().Zero();
	if (wheelsLength > 0)
	{
		m_wheelsLength = wheelsLength;
		m_wheels = new MobileOGLObject*[m_wheelsLength + 1];
		SetChildsLength(wheelsLength + 1); // X rodes, 1 carroceria, 1 camara
	}
	else
	{
		m_wheelsLength = 0;
		m_wheels = NULL;
	}
}

void Car::ResetLaps() {
	m_laps = 0;
}

void Car::UpdatePU()
{
	
	if (m_GetPU > 0) {
	
		m_GetPU--;

	}

}

bool Car::CheckPU()
{
	if (m_GetPU <= 0) {

		return true;
	
	}
	
	return false;
}

void Car::SetMoveValues(float dist)
{
	m_boosts = m_initialBoosts;
	m_friction = m_frictionC / dist;
	m_gravity = m_gravityC / dist;
	m_boostSpeed = m_boostSpeedC / dist;
	m_brakeSpeed = m_brakeSpeedC / dist;
	m_speed = 0;
	m_progress = 0;
	m_laps = 0;
}

void Car::SetWheel(int index, GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
	if (index >= 0 && index < m_wheelsLength)
	{
		m_wheels[index] = new MobileOGLObject(glIndex, glTextIndex, position, rotation, scale);
		SetChild(index + 1, m_wheels[index]);
	}
}

void Car::SetBody(GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
	m_body = MobileOGLObject(glIndex, glTextIndex, position, rotation, scale);
	SetChild(0, &m_body);
}

void Car::Move(Vector3 pos, Vector3 dir)
{
	m_progress += m_speed;
	if (m_progress > 1) {

		m_progress -= 1;
		m_laps++;

	}

	if (m_progress < 0) m_progress += 1;
	
	//rotation = Vector3(Vector3(1, 0, 0).AngleXBtw(dir), 0, 0);
	//dir = Vector3().Zero();
	dir.Normalize();
	Vector3 rotation = dir.GetAngles();
	//rotation = rotation * RAD_TO_DEG;

	//rotation = Vector3(Vector3(1, 0, 0).AngleXBtw(dir), 0, 0);

	//https://math.stackexchange.com/questions/575472/getting-angles-for-rotating-3d-vector-to-point-in-direction-of-another-3d-ve

	//int x = 0, y = 0, z = 0;
	//Vector3 rotation = Vector3(x, y, z).GetAngles();

	//rotation += Vector3(0, pi/2, 0);
	//rotation -= Vector3(0, (pi / 2), 0);

	//if (dir.Y() < 0) rotation = Vector3(rotation.X(), rotation.Y(), -rotation.Z());
	if (dir.Z() > 0) rotation = Vector3(-rotation.X(), rotation.Y(), rotation.Z());
	//rotation = Vector3(rx, ry, rz).GetAngles();
	
	pos += Vector3(0, 5, 0);
	SetRotation(rotation);
	SetPosition(pos);
	m_direction = dir;

	// A través del raonament amb el dot product concluim....
	m_speed += m_gravity * -1 * dir.Y();

	if (m_speed > 0)
	{
		if (m_speed - m_friction < 0) m_speed = 0;
		else m_speed -= m_friction;
	}
	else if (m_speed < 0)
	{
		if (m_speed + m_friction > 0) m_speed = 0;
		else m_speed += m_friction;
	}
}

Vector3 Car::GetDirection() const
{
	return m_direction;
}

void Car::Boost()
{
	if (m_boosts > 0)
	{
		m_speed += m_boostSpeed;
		m_boosts--;
	}
}

void Car::Brake()
{
	if (m_speed < 0)
	{
		if (m_speed + m_brakeSpeed > 0) m_speed = 0;
		else m_speed += m_brakeSpeed;
	}
	else if (m_speed > 0)
	{
		if (m_speed - m_brakeSpeed < 0) m_speed = 0;
		else m_speed -= m_brakeSpeed;
	}
}

float Car::GetProgress() const
{
	return m_progress;
}

void Car::ResetProgress()
{
	m_progress = 0;
	m_speed = 0;
	m_boosts = m_initialBoosts;
}

void Car::AddBoost()
{
	if (m_boosts < m_maxBoosts) {
		
		m_boosts++;
		m_GetPU = TIME_PU;

	}
}

int Car::getBoosts()
{
	return m_boosts;
}

int Car::getLaps()
{

	return m_laps;

}

Car::~Car()
{
	//delete[] m_wheels;
}
