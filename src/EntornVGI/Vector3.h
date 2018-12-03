#pragma once
#include <math.h>

#define RAD_TO_DEG (180.0 / pi)

class Vector3
{
private:
	float m_x;
	float m_y;
	float m_z;

public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);

	static Vector3 Zero();
	static Vector3 One();

	float X() const;
	float Y() const;
	float Z() const;

	void Inc(float x, float y, float z);
	void Dec(float x, float y, float z);

	float Distance(Vector3 t);
	float DotP(Vector3 v);
	Vector3 DirCrossP(Vector3 v);
	Vector3 CrossP(Vector3 v);
	float Magnitude() const;
	void Normalize();
	float AngleXBtw(Vector3 v);
	float AngleX() const;
	float AngleY() const;
	float AngleZ() const;
	Vector3 GetAngles() const;
	void RotateY(float d, Vector3 r);

	//Vector3 Direction(Vector3 t);

	//TODO: Operators overload & methods (+, -, *, /, scalate, dot prod, unari, etc.)

	// Operators
	Vector3 & operator=(const Vector3 &v);
	Vector3 & operator+=(const Vector3 &v);
	Vector3 operator+(const Vector3 &v);
	Vector3 & operator-=(const Vector3 &v);
	Vector3 operator-(const Vector3 &v);
	Vector3 & operator*=(float s);
	Vector3 operator*(float s);
	Vector3 & operator/=(float s);
	Vector3 operator/(float s);

	~Vector3();
};

