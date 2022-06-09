#pragma once
#include "cimage.h"


class cImageBlock :
	public cImage
{
public:
	RECT	   m_Rect;

public:
	cImageBlock(void);
	~cImageBlock(void);

	void Draw(HDC hdc, int destX, int destY, 
		int width, int height, int srcX, int srcY);
};
