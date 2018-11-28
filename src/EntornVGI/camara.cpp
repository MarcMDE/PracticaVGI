#include "stdafx.h"
#include "camara.h"

camara::camara() {

	// Constructor

	m_eyeX = 0;
	m_eyeY = 0;
	m_eyeZ = 0;
	//m_position = Vector3().Zero();

	m_centerX = 0;
	m_centerY = 0;
	m_centerZ = 0;

	m_upX = 0;
	m_upY = 0;
	m_upZ = 0;

}

camara::camara(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ) {

	// Constructor

	setCamEye(eyeX, eyeY, eyeZ);
	setCamCenter(centerX, centerY, centerZ);
	setCamUp(upX, upY, upZ);

}


camara::~camara() {

	// Destructor 

}

void camara::getCam() {

	gluLookAt(m_eyeX, m_eyeY, m_eyeZ, m_centerX, m_centerY, m_centerZ, m_upX, m_upY, m_upZ);
	//gluLookAt(m_position.X(), m_position.Y(), m_position.Z(), m_centerX, m_centerY, m_centerZ, m_upX, m_upY, m_upZ);

}

void camara::getIlu() {

	//Iluminacio();

}

void camara::setCamEye(GLdouble X, GLdouble Y, GLdouble Z) {

	m_eyeX = X;
	m_eyeY = Y;
	m_eyeZ = Z;
	//m_position = Vector3(X, Y, Z);

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

void camara::Draw()
{
	getCam();
}
