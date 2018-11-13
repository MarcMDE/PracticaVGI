#pragma once
#include "MobileOGLObject.h"
#include "Vector3.h"

class DynamicOGLObject : public MobileOGLObject
{
private:
	Vector3 m_direction;
	Vector3 m_velocity;
	float m_mass;
	
public:
	DynamicOGLObject() : MobileOGLObject(), m_direction(Vector3().Zero()), m_velocity(Vector3().Zero()) {};
	DynamicOGLObject(GLuint glIndex) : MobileOGLObject(glIndex), m_direction(Vector3().Zero()), m_velocity(Vector3().Zero()) {};
	DynamicOGLObject(GLuint glIndex, Vector3 position) : MobileOGLObject(glIndex, position), m_direction(Vector3().Zero()), m_velocity(Vector3().Zero()) {};
	DynamicOGLObject(GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale) : 
		MobileOGLObject(glIndex, position, rotation, scale), m_direction(Vector3().Zero()), m_velocity(Vector3().Zero()) {};



	~DynamicOGLObject();
};

