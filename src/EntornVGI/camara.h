#pragma once

#include "visualitzacio.h"
#include "OGLObject.h"
#include "Vector3.h"

class camara : public OGLObject{

	// Variables
	public:

		GLdouble m_eyeX;
		GLdouble m_eyeY;
		GLdouble m_eyeZ;

		GLdouble m_centerX;
		GLdouble m_centerY;
		GLdouble m_centerZ;

		GLdouble m_upX;
		GLdouble m_upY;
		GLdouble m_upZ;

	// Funcions i mètodes
	public:

		camara();
		camara(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ);

		~camara();

		void getCam();

		void setCamEye(GLdouble X, GLdouble Y, GLdouble Z);
		void setCamCenter(GLdouble X, GLdouble Y, GLdouble Z);
		void setCamUp(GLdouble X, GLdouble Y, GLdouble Z);

		void getIlu();

		void setIlu();

		void Draw();

};

