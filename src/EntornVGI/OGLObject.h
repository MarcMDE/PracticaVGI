#pragma once

#include "Vector3.h"

class OGLObject
{
protected:
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	GLuint m_glIndex;
	GLuint m_glTextIndex;
	OGLObject **m_childs;
	int m_childsLength;

public:
	// Constructors-------------------------
	OGLObject();
	// glIndex i/o glTextIndex han de ser -1 si no model o no textura
	OGLObject(GLuint glIndex, GLuint glTextIndex);
	// glIndex i/o glTextIndex han de ser -1 si no model o no textura
	OGLObject(GLuint glIndex, GLuint glTextIndex, Vector3 position);
	// glIndex i/o glTextIndex han de ser -1 si no model o no textura
	OGLObject(GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale);
	~OGLObject();

	// Getters------------------------------
	const Vector3& GetPosition() const;
	const Vector3& GetRotation() const;
	const Vector3& GetScale() const;
	//GLuint GetGLIndex() const;
	OGLObject* GetChild(int i);
	int GetChildsLength() const;

	// Setters------------------------------
	void SetChilds(OGLObject **childs, int lenght);
	void SetChildsLength(int lenght);
	void SetChild(int index, OGLObject *child);

	// Draw---------------------------------
	virtual void Draw();

	// Operators----------------------------

};

