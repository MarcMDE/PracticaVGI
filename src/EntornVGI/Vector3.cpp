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

float Vector3::Distance(Vector3 t)
{
	Vector3 f = (*this) - t;

	return sqrtf(f.m_x*f.m_x + f.m_y*f.m_y + f.m_z*f.m_z);
}

float Vector3::DotP(Vector3 v)
{
	return v.m_x*m_x + v.m_y*m_y + v.m_z*m_z;
}

Vector3 Vector3::DirCrossP(Vector3 v)
{
	return Vector3(	m_y*v.m_z - m_z*v.m_y,
					m_z*v.m_x - m_x*v.m_z,
					m_x*v.m_y - m_y*v.m_x);
}

float Vector3::Magnitude() const
{
	return sqrtf(m_x*m_x + m_y*m_y + m_z*m_z);
}

void Vector3::Normalize()
{
	*this /= Magnitude();
}

float Vector3::AngleXBtw(Vector3 v)
{
	//v = Vector3(v.X(), 0, v.Z());
	//Vector3 me = Vector3(m_x, 0, m_z);
	Vector3 me = *this;
	float vMag = v.Magnitude();
	float mag = me.Magnitude();

	float ret = me.DotP(v) / (vMag * mag);

	return acos(ret);
}

float Vector3::AngleX() const
{
	return acos(m_x / Magnitude());
}
float Vector3::AngleY() const
{
	return acos(m_y / Magnitude());
}
float Vector3::AngleZ() const
{
	return acos(m_z / Magnitude());
}

Vector3 Vector3::GetAngles() const
{
	float magnitude = Magnitude();
	if (magnitude == 0) return Vector3().Zero();

	Vector3 ret = Vector3(
		acos(m_x / magnitude),
		acos(m_y / magnitude),
		acos(m_z / magnitude));

	return ret;
}

void Vector3::RotateY(float d, Vector3 r)
{
	float sind = sin(d);
	float cosd = cos(d);

	*this -= r;

	m_x = m_x * cosd + m_z * sind;
	m_z = -m_x * sind + m_z * cosd;

	*this += r;
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
