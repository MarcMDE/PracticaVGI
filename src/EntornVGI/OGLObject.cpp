#include "stdafx.h"
#include "OGLObject.h"

OGLObject::OGLObject()
{
	m_glIndex = 0;
	m_position = Vector3().Zero();
	m_rotation = Vector3().One();
	m_scale = Vector3().One();
	m_childs = NULL;
	m_childsLength = 0;
}

OGLObject::OGLObject(GLuint glIndex)
{
	m_glIndex = glIndex;
	m_position = Vector3().Zero();
	m_rotation = Vector3().One();
	m_scale = Vector3().One();
	m_childs = NULL;
	m_childsLength = 0;
}

OGLObject::OGLObject(GLuint glIndex, Vector3 position)
{
	m_glIndex = glIndex;
	m_position = position;
	m_rotation = Vector3().One();
	m_scale = Vector3().One();
	m_childs = NULL;
	m_childsLength = 0;
}

OGLObject::OGLObject(GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale)
{
	m_glIndex = glIndex;
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	m_childs = NULL;
	m_childsLength = 0;
}

const Vector3& OGLObject::GetPosition() const
{
	return m_position;
}

const Vector3& OGLObject::GetRotation() const
{
	return m_rotation;
}

const Vector3& OGLObject::GetScale() const
{
	return m_scale;
}

GLuint OGLObject::GetGLIndex() const
{
	return m_glIndex;
}

OGLObject * OGLObject::GetChild(int i)
{
	if (i < m_childsLength)
	{
		// TODO: Assert
	}
	
	return m_childs[i];
}

int OGLObject::GetChildsLength() const
{
	return m_childsLength;
}

OGLObject * OGLObject::GetOGLObject()
{
	return this;
}

void OGLObject::SetChilds(OGLObject ** childs, int lenght)
{
	if (m_childs != NULL)
	{
		for (int i = 0; i < m_childsLength; i++)
		{
			delete m_childs[i];
		}

		delete m_childs;
	}

	m_childsLength = lenght;
	m_childs = childs;
}

void OGLObject::SetChildsLength(int lenght)
{
	if (m_childs != NULL)
	{
		for (int i = 0; i < m_childsLength; i++)
		{
			delete m_childs[i];
		}

		delete m_childs;
	}
	m_childsLength = lenght;
	m_childs = new OGLObject*[m_childsLength];
}

void OGLObject::SetChild(int index, OGLObject * child)
{
	m_childs[index] = child;
}

void OGLObject::Draw()
{
	if (m_glIndex != 0)
	{
		glCallList(m_glIndex);
	}
}

OGLObject::~OGLObject()
{
	if (m_childs != NULL)
	{
		for (int i = 0; i < m_childsLength; i++)
		{
			delete m_childs[i];
		}

		delete m_childs;
	}

	m_childs = NULL;
	m_childsLength = 0;
}
