#pragma once
#include <math.h>

class UIButton
{
private:
	int m_posX;
	int m_posY;
	int m_w;
	int m_h;
	int m_texture;

public:
	UIButton();
	~UIButton();

	void Set(int x, int y, int w, int h, int t);
	bool IsClicked(int x, int y) const;
	void Draw() const;
};

