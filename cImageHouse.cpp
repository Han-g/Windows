#include "cImageHouse.h"
#include "Define.h"

cImageHouse::cImageHouse(void)
{
}

cImageHouse::~cImageHouse(void)
{
}

void cImageHouse::DrawTrans(HDC hdc, int destX, int destY, int width, int height)
{
	GdiTransparentBlt(hdc,
		destX, destY, width, height,
		m_DC, 0, 0, width, height, COLOR);

	m_Pos.x = destX;
	m_Pos.y = destY;

	m_Rect.left = destX;
	m_Rect.right = destX + OBJ_TILE_W;
	m_Rect.top = destY + OBJ_HOUSE_H - OBJ_TILE_H;
	m_Rect.bottom = destY + OBJ_HOUSE_H;
}