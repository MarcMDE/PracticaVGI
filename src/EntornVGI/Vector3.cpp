#include "stdafx.h"
#include "Vector3.h"


Vector3::Vector3()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector3::Vector3(const Vector3 & v)
{
	m_x = v.m_x;
	m_y = v.m_y;
	m_z = v.m_z;
}

float Vector3::X() const
{
	return m_x;
}
float Vector3::Y() const
{
	return m_y;
}
float Vector3::Z() const
{
	return m_z;
}
Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::One()
{
	return Vector3(1, 1, 1);
}

void Vector3::Inc(float x, float y, float z)
{
	m_x += x;
	m_y += y;
	m_z += z;
}

void Vector3::Dec(float x, float y, float z)
{
	m_x -= x;
	m_y -= y;
	m_z -= z;
}

Vector3 & Vector3::operator=(const Vector3 &v)
{
	m_x = v.m_x;
	m_y = v.m_y;
	m_z = v.m_z;

	return *this;
}

Vector3 & Vector3::operator+=(const Vector3 &v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;

	return *this;
}

Vector3 Vector3::operator+(const Vector3 &v)
{
	Vector3 ret;
	ret.m_x = m_x + v.m_x;
	ret.m_y = m_y + v.m_y;
	ret.m_z = m_z + v.m_z;

	return ret;
}

Vector3 & Vector3::operator-=(const Vector3 &v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;

	return *this;
}

Vector3 Vector3::operator-(const Vector3 &v)
{
	Vector3 ret;
	ret.m_x = m_x - v.m_x;
	ret.m_y = m_y - v.m_y;
	ret.m_z = m_z - v.m_z;

	return ret;
}

Vector3 & Vector3::operator*=(float s)
{
	m_x *= s;
	m_y *= s;
	m_z *= s;

	return *this;
}

Vector3 Vector3::operator*(float s)
{
	Vector3 ret;
	ret.m_x = m_x * s;
	ret.m_y = m_y * s;
	ret.m_z = m_z * s;

	return ret;
}

Vector3 & Vector3::operator/=(float s)
{
	m_x /= s;
	m_y /= s;
	m_z /= s;

	return *this;
}

Vector3 Vector3::operator/(float s)
{
	Vector3 ret;
	ret.m_x = m_x / s;
	ret.m_y = m_y / s;
	ret.m_z = m_z / s;

	return ret;
}


Vector3::~Vector3()
{
}