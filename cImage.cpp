#include "cImage.h"
#include "Define.h"

cImage::cImage(void)
{
}

cImage::~cImage(void)
{
}

HRESULT cImage::Init(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;

	HDC hdc = GetDC(g_hWnd);

	m_DC = CreateCompatibleDC(hdc);
	m_newBit = CreateCompatibleBitmap(hdc, width, height);
	m_oldBit = (HBITMAP)SelectObject(m_DC, m_newBit);

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT cImage::Init(const char* filename, int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;

	HDC hdc = GetDC(g_hWnd);

	m_DC = CreateCompatibleDC(hdc);
	m_newBit = (HBITMAP)LoadImage(g_hInst, filename,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_oldBit = (HBITMAP)SelectObject(m_DC, m_newBit);

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void cImage::Release(void)
{
	DeleteObject(SelectObject(m_DC, m_oldBit));
	DeleteDC(m_DC);
}

void cImage::Draw(HDC hdc, int x, int y)
{
	BitBlt(hdc, x, y, m_nWidth, m_nHeight,
		m_DC, 0, 0, SRCCOPY);
}

void cImage::Draw(HDC hdc, int x, int y, int srcX, int srcY)
{
	BitBlt(hdc, x, y, m_nWidth, m_nHeight,
		m_DC, srcX, srcY, SRCCOPY);
}

void cImage::Draw(HDC hdc, int destX, int destY,
	int width, int height, int srcX, int srcY)
{
	BitBlt(hdc, destX, destY, width, height,
		m_DC, srcX, srcY, SRCCOPY);
}

void cImage::DrawTrans(HDC hdc, int x, int y,
	int srcX, int srcY, int srcW,
	int srcH)
{
	GdiTransparentBlt(hdc, x, y, srcW, srcH,
		m_DC, srcX, srcY, srcW, srcH, COLOR);
}

HDC cImage::GetBitDC(void)
{
	return m_DC;
}


int cImage::GetPosX(void)
{
	return m_Pos.x;
}

int cImage::GetPosY(void)
{
	return m_Pos.y;
}

POINT& cImage::GetPoint(void)
{
	return m_Pos;
}

RECT& cImage::GetRect(void)
{
	return m_Rect;
}

void cImage::SetPoint(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

void cImage::SetRect(int left, int top, int right, int bottom)
{
	m_Rect.left = left;
	m_Rect.top = top;
	m_Rect.right = right;
	m_Rect.bottom = bottom;
}