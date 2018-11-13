#include "stdafx.h"
#include "MobileOGLObject.h"

MobileOGLObject::~MobileOGLObject()
{
}

void MobileOGLObject::SetPosition(Vector3 p)
{
	m_position = p;
}

void MobileOGLObject::SetRotation(Vector3 r)
{
	m_rotation = r;
}

void MobileOGLObject::SetScale(Vector3 s)
{
	m_scale = s;
}

void MobileOGLObject::Translate(Vector3 d)
{
	m_position += d;
}

void MobileOGLObject::Rotate(Vector3 d)
{
	m_rotation += d;
}

void MobileOGLObject::Scalate(Vector3 d)
{
	m_scale += d;
}
