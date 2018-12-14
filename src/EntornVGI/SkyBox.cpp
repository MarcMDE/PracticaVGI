#include "stdafx.h"
#include "SkyBox.h"

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::Draw()
{
	glBindTexture(GL_TEXTURE_2D, textura);
	// glutSolidCube(10);
	glBegin(GL_QUADS);
	
	// CARA - Z
	glTexCoord2f(0.0, 0.0); glVertex3f(-s, -s, -s);
	glTexCoord2f(0.0, 1.0); glVertex3f(-s, s, -s);
	glTexCoord2f(1.0, 1.0); glVertex3f(s, s, -s);
	glTexCoord2f(1.0, 0.0); glVertex3f(s, -s, -s);
	// CARA + Z
	glTexCoord2f(0.0, 0.0); glVertex3f(-s, -s, s);
	glTexCoord2f(0.0, 1.0); glVertex3f(-s, s, s);
	glTexCoord2f(1.0, 1.0); glVertex3f(s, s, s);
	glTexCoord2f(1.0, 0.0); glVertex3f(s, -s, s);
	// CARA + X
	glTexCoord2f(0.0, 0.0); glVertex3f(s, -s, -s);
	glTexCoord2f(0.0, 1.0); glVertex3f(s, s, -s);
	glTexCoord2f(1.0, 1.0); glVertex3f(s, s, s);
	glTexCoord2f(1.0, 0.0); glVertex3f(s, -s, s);
	// CARA - X
	glTexCoord2f(0.0, 0.0); glVertex3f(-s, -s, -s);
	glTexCoord2f(0.0, 1.0); glVertex3f(-s, s, -s);
	glTexCoord2f(1.0, 1.0); glVertex3f(-s, s, s);
	glTexCoord2f(1.0, 0.0); glVertex3f(-s, -s, s);
	// CARA - Y
	glTexCoord2f(0.0, 0.0); glVertex3f(-s, -s, s);
	glTexCoord2f(0.0, 1.0); glVertex3f(-s, -s, -s);
	glTexCoord2f(1.0, 1.0); glVertex3f(s, -s, -s);
	glTexCoord2f(1.0, 0.0); glVertex3f(s, -s, s);
	// CARA + Y
	glTexCoord2f(1/4, 0.0); glVertex3f(-s, s, -s);
	glTexCoord2f(1/4, 1/4); glVertex3f(-s, s, s);
	glTexCoord2f(2/4, 0.0); glVertex3f(s, s, s);
	glTexCoord2f(2/4, 1/4); glVertex3f(s, s, -s);

	glEnd();
}
