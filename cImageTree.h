#pragma once
#include "cimage.h"

class cImageTree :
	public cImage
{
public:
	RECT	   m_Rect;

public:
	cImageTree(void);
	~cImageTree(void);

	void DrawTrans(HDC hdc, int destX, int destY,
		int width, int height);
};
