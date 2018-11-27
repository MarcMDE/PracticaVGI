#pragma once

#include "Vector3.h"

class OGLObject
{
protected:
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	GLuint m_glIndex;
	OGLObject **m_childs;
	int m_childsLength;

public:
	// Constructors-------------------------
	OGLObject();
	OGLObject(GLuint glIndex);
	OGLObject(GLuint glIndex, Vector3 position);
	OGLObject(GLuint glIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	~OGLObject();

	// Getters------------------------------
	const Vector3& GetPosition() const;
	const Vector3& GetRotation() const;
	const Vector3& GetScale() const;
	GLuint GetGLIndex() const;
	OGLObject* GetChild(int i);
	int GetChildsLength() const;
	const OGLObject& GetOGLObject() const;

	// Setters------------------------------
	void SetChilds(OGLObject **childs, int lenght);
	void SetChildsLength(int lenght);
	void SetChild(int index, OGLObject *child);

	// Draw---------------------------------
	virtual void Draw();

	// Operators----------------------------

};

