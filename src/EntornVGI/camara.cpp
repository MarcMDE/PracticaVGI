#include "stdafx.h"
#include "camara.h"
#include "visualitzacio.h"


camara::camara() {

	// Constructor

	m_eyeX = 0.0f;
	m_eyeY = 0.0f;
	m_eyeZ = 0.0f;

	m_centerX = 0.0f;
	m_centerY = 0.0f;
	m_centerZ = 0.0f;

	m_upX = 0.0f;
	m_upY = 0.0f;
	m_upZ = 0.0f;

}

camara::camara(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ) {

	// Constructor

	setCamEye(eyeX, eyeY, eyeZ);
	setCamEye(centerX, centerY, centerZ);
	setCamEye(upX, upY, upZ);

}


camara::~camara() {

	// Destructor 

}

void camara::getCam() {

	gluLookAt(m_eyeX, m_eyeY, m_eyeZ, m_centerX, m_centerY, m_centerZ, m_upX, m_upY, m_upZ);

}

void camara::getIlu() {

	//

}

void camara::setCamEye(GLdouble X, GLdouble Y, GLdouble Z) {

	m_eyeX = X;
	m_eyeY = Y;
	m_eyeZ = Z;

}

void camara::setCamCenter(GLdouble X, GLdouble Y, GLdouble Z) {

	m_centerX = X;
	m_centerY = Y;
	m_centerZ = Z;

}

void camara::setCamUp(GLdouble X, GLdouble Y, GLdouble Z) {

	m_upX = X;
	m_upY = Y;
	m_upZ = Z;

}

void camara::setIlu() {

	//

}
