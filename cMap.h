#pragma once

#include "Define.h"
#include <fstream>
#define MAP cMap::GetInstance()

class cMap
{
private:
	std::ifstream	m_File;
	char			m_Tile[STAGE_HEIGHT][STAGE_WIDTH];
	RECT			m_rcTile[STAGE_HEIGHT][STAGE_WIDTH];
	bool			m_bRoad[STAGE_HEIGHT][STAGE_WIDTH];
	bool			m_bItem[STAGE_HEIGHT][STAGE_WIDTH];
private:
	cMap(void);

public:
	~cMap(void);

	static cMap& GetInstance();

	void MapInit(LPCSTR filename);
	void Release(void);
	bool GetRoad(int x, int y);
	char GetTile(int x, int y);
	RECT GetRectTile(int x, int y);
	void SetTileRect(int x, int y, int left, int top, int right, int bottom);
	void SetBoolRoad(bool b, int x, int y);

	bool GetBoolItem(int x, int y);
	void SetBoolItem(bool b, int x, int y);
};

