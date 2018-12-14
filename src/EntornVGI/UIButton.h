#pragma once
#include <math.h>

class UIButton
{
private:
	const int m_selectOffset = 5;
	int m_posX;
	int m_posY;
	int m_w;
	int m_h;
	int m_texture;
	bool m_selected;

public:
	UIButton();
	~UIButton();

	void Set(int x, int y, int w, int h, int t);
	bool IsClicked(int x, int y) const;
	void Draw() const;
	void Select();
	void Unselect();
};

