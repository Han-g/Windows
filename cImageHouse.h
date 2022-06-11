#pragma once

#include "cimage.h"

class cImageHouse :
	public cImage
{
public:
	RECT	   m_Rect;

public:
	cImageHouse(void);
	~cImageHouse(void);

	void DrawTrans(HDC hdc, int destX, int destY,
		int width, int height);
};

