#include "cImageBlock.h"
#include "Define.h"

cImageBlock::cImageBlock(void)
{
}

cImageBlock::~cImageBlock(void)
{
}

void cImageBlock::Draw(HDC hdc, int destX, int destY, int width, int height, int srcX, int srcY)
{
	BitBlt(hdc, destX, destY, width, height,
		m_DC, srcX, srcY, SRCCOPY);

	m_Pos.x = destX;
	m_Pos.y = destY;

	m_Rect.left		= destX;
	m_Rect.right	= destX + OBJ_TILE_W;
	m_Rect.top		= destY + OBJ_BLOCK_H - OBJ_TILE_H;
	m_Rect.bottom	= destY + OBJ_BLOCK_H;
}