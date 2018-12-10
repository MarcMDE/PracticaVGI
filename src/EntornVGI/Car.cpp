#include "stdafx.h"
#include "Car.h"

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
	//rotation = Vector3(Vector3(1, 0, 0).AngleXBtw(dir), 0, 0);
	Vector3 rotation = dir.GetAngles();
	//rotation = rotation * RAD_TO_DEG;

	//rotation = Vector3(Vector3(1, 0, 0).AngleXBtw(Vector3(rx, ry, rz)), 0, 0);

	//https://math.stackexchange.com/questions/575472/getting-angles-for-rotating-3d-vector-to-point-in-direction-of-another-3d-ve

	//int x = 0, y = 0, z = 0;
	//Vector3 rotation = Vector3(x, y, z).GetAngles();

	rotation -= Vector3(0, (pi / 2), 0);

	if (dir.Z() > 0) rotation = Vector3(-rotation.X(), rotation.Y(), rotation.Z());
	//rotation = Vector3(rx, ry, rz).GetAngles();
	
	pos += Vector3(0, 5, 0);

	SetRotation(rotation);
	SetPosition(pos);
}

Car::~Car()
{
	delete[] m_wheels;
}
