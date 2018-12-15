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
	glTexCoord2f(0.75, 0.5); glVertex3f(-s, -s, -s);
	glTexCoord2f(0.75, 0.75); glVertex3f(-s, s, -s);
	glTexCoord2f(1.0, 0.75); glVertex3f(s, s, -s);
	glTexCoord2f(1.0, 0.5); glVertex3f(s, -s, -s);
	// CARA + Z
	glTexCoord2f(0.5, 0.5); glVertex3f(-s, -s, s);
	glTexCoord2f(0.5, 0.75); glVertex3f(-s, s, s);
	glTexCoord2f(0.25, 0.75); glVertex3f(s, s, s);
	glTexCoord2f(0.25, 0.5); glVertex3f(s, -s, s);
	// CARA + X
	glTexCoord2f(0, 0.5); glVertex3f(s, -s, -s);
	glTexCoord2f(0, 0.75); glVertex3f(s, s, -s);
	glTexCoord2f(0.25, 0.75); glVertex3f(s, s, s);
	glTexCoord2f(0.25, 0.5); glVertex3f(s, -s, s);
	// CARA - X
	glTexCoord2f(0.75, 0.5); glVertex3f(-s, -s, -s);
	glTexCoord2f(0.75, 0.75); glVertex3f(-s, s, -s);
	glTexCoord2f(0.5, 0.75); glVertex3f(-s, s, s);
	glTexCoord2f(0.5, 0.5); glVertex3f(-s, -s, s);
	// CARA - Y
	glTexCoord2f(0.5, 0.5); glVertex3f(-s, -s, s);
	glTexCoord2f(0.5, 0.25); glVertex3f(-s, -s, -s);
	glTexCoord2f(0.25, 0.25); glVertex3f(s, -s, -s);
	glTexCoord2f(0.25, 0.5); glVertex3f(s, -s, s);
	// CARA + Y
	glTexCoord2f(0.5, 1.0); glVertex3f(-s, s, -s);
	glTexCoord2f(0.5, 0.75); glVertex3f(-s, s, s);
	glTexCoord2f(0.25, 0.75); glVertex3f(s, s, s);
	glTexCoord2f(0.25, 1.0); glVertex3f(s, s, -s);

	glEnd();
}
