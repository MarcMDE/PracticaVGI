#pragma once
#include "OGLObject.h"
#include "Vector3.h"

class MobileOGLObject : public OGLObject
{
public:
	// Constructors
	MobileOGLObject() : OGLObject() {};
	MobileOGLObject(GLuint glIndex, GLuint glTextIndex) : OGLObject(glIndex, glTextIndex) {};
	MobileOGLObject(GLuint glIndex, GLuint glTextIndex, Vector3 position) : OGLObject(glIndex, glTextIndex, position) {};
	MobileOGLObject(GLuint glIndex, GLuint glTextIndex, Vector3 position, Vector3 rotation, Vector3 scale) :
		OGLObject(glIndex, glTextIndex, position, rotation, scale) {};
	~MobileOGLObject();

	// Setters
	void SetPosition(Vector3 p);
	void SetRotation(Vector3 r);
	void SetScale(Vector3 s);

	// Funcs
	void Translate(Vector3 d);
	void Rotate(Vector3 d);
	void Scalate(Vector3 d);
};

