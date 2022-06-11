#include "cMap.h"

cMap::cMap(void)
{
}

cMap::~cMap(void)
{
}

cMap& cMap::GetInstance()
{
	static cMap Instance;
	return Instance;
}

void cMap::MapInit(LPCSTR filename)
{
	m_File.open(filename);
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			m_bItem[i][j] = false;
			//타일을 읽어들인다
			m_File >> m_Tile[i][j];
			//타일에 대한 충돌처리
			if (m_Tile[i][j] != '0')
			{
				m_rcTile[i][j].left = j * OBJ_TILE_W + STAGE_START_X;
				m_rcTile[i][j].right = m_rcTile[i][j].left + OBJ_TILE_W;
				m_rcTile[i][j].top = i * OBJ_TILE_H + STAGE_START_Y;
				m_rcTile[i][j].bottom = m_rcTile[i][j].top + OBJ_TILE_H;
				m_bRoad[i][j] = false;
			}
			else
				m_bRoad[i][j] = true;
		}
	}
	m_File.close();
}

void cMap::Release(void)
{
}
char cMap::GetTile(int x, int y)
{
	return m_Tile[y][x];
}
bool cMap::GetRoad(int x, int y)
{
	return m_bRoad[y][x];
}
RECT cMap::GetRectTile(int x, int y)
{
	return m_rcTile[y][x];
}
void cMap::SetTileRect(int x, int y, int left, int top, int right, int bottom)
{
	m_rcTile[y][x].left = left;
	m_rcTile[y][x].top = top;
	m_rcTile[y][x].right = right;
	m_rcTile[y][x].bottom = bottom;
}
void cMap::SetBoolRoad(bool b, int x, int y)
{
	m_bRoad[y][x] = b;
}
bool cMap::GetBoolItem(int x, int y)
{
	return m_bItem[y][x];
}
void cMap::SetBoolItem(bool b, int x, int y)
{
	m_bItem[y][x] = b;
}