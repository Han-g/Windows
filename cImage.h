#pragma once
#include "Define.h"

class cImage
{
protected:
	HDC				m_DC;
	HBITMAP			m_newBit;
	HBITMAP			m_oldBit;

	int				m_nWidth;
	int				m_nHeight;

public:
	POINT		m_Pos;
	RECT		m_Rect;

public:
	cImage(void);
	~cImage(void);

	HRESULT Init(int width, int height);
	HRESULT Init(const char* filename, int width, int height);

	void Release(void);

	void Draw(HDC hdc, int x, int y);
	void Draw(HDC hdc, int x, int y, int srcX, int srcY);
	void Draw(HDC hdc, int destX, int destY,
		int width, int height, int srcX, int srcY);
	void DrawTrans(HDC hdc, int x, int y, int srcX, int srcY,
		int srcW, int srcH);

	HDC GetBitDC(void);

	int		GetPosX(void);
	int		GetPosY(void);
	POINT& GetPoint(void);
	RECT& GetRect(void);

	void	SetPoint(int x, int y);
	void	SetRect(int left, int top, int right, int bottom);
};

