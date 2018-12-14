#include "stdafx.h"
#include "UIButton.h"


UIButton::UIButton()
{
}


UIButton::~UIButton()
{
}

void UIButton::Set(int x, int y, int w, int h, int t)
{
	m_posX = x;
	m_posY = y;
	m_w = w;
	m_h = h;
	m_texture = t;
}

bool UIButton::IsClicked(int x, int y) const
{
	if (abs(m_posX - x) <= m_w / 2)
	{
		if (abs(m_posY - y) <= m_h / 2)
		{
			return true;
		}
	}

	return false;
}

void UIButton::Draw() const
{
	if (m_selected)
	{
		//glColor3f(1.0f, 0.0f, 0.0f); // Red
		glBegin(GL_QUADS);
			glVertex2f(m_posX + m_w / 2 + m_selectOffset, m_posY + m_h / 2 + m_selectOffset);
			glVertex2f(m_posX - m_w / 2 - m_selectOffset, m_posY + m_h / 2 + m_selectOffset);
			glVertex2f(m_posX - m_w / 2 - m_selectOffset, m_posY - m_h / 2 - m_selectOffset);
			glVertex2f(m_posX + m_w / 2 + m_selectOffset, m_posY - m_h / 2 - m_selectOffset);
		glEnd();
		//glColor3f(1.0f, 0.0f, 0.0f); // Red
	}
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 0.0); glVertex2f(m_posX + m_w / 2, m_posY + m_h / 2);
		glTexCoord2f(0.0, 0.0); glVertex2f(m_posX - m_w / 2, m_posY + m_h / 2);
		glTexCoord2f(0.0, 1.0); glVertex2f(m_posX - m_w / 2, m_posY - m_h / 2);
		glTexCoord2f(1.0, 1.0); glVertex2f(m_posX + m_w / 2, m_posY - m_h / 2);
	glEnd();
}

void UIButton::Select()
{
	m_selected = true;
}

void UIButton::Unselect()
{
	m_selected = false;
}
