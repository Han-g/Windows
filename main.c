#define window_size_w 800
#define window_size_d 800
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "resource.h"

int line_w = (window_size_w - 40) / 40, line_d = (window_size_d - 40) / 40, location = 0;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, window_size_w, window_size_d, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

typedef struct BAKCGROUND {
	int MAX_X, MAX_Y;
}background;
typedef struct CHARACTER {
	int x, y, state;
	int speed, num_bubble, bubble_len;
}Character;
typedef struct BUBBLE {
	int x, y, len;
}Bubble;
typedef struct OBJECT {
	int x, y;
}Object;
typedef struct ITEM {
	int kind;
}Item;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc, memdc;
	//HDC mem1dc, mem2dc;
	static HBITMAP hBit1, hBit2;
	//HBITMAP oldBit1, oldBit2;
	static int reverse = 0, full = 0, sec = 0, trd = 0;
	static int x = 0, y = 0, w = 330, h = 240, mx = 0, my = 0, mw = 1600, mh = 1200;
	static Character character[2];
	static Object obj;
	static Item item;

	//kdhfaofsjkjfalj

	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		hBit1 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(101));
		break;
	case WM_TIMER:

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (character[0].x < window_size_w) ++character[0].x;
			break;
		case VK_RIGHT:
			if (character[0].x > 0) --character[0].x;
			break;
		case VK_UP:
			if (character[0].y > 0) --character[0].y;
			break;
		case VK_DOWN:
			if (character[0].y < window_size_d) ++character[0].y;
			break;
		case VK_LSHIFT:

			break;
		case '4':
			if (character[1].x < window_size_w) ++character[1].x;
			break;
		case '6':
			if (character[1].x > 0) --character[1].x;
			break;
		case '8':
			if (character[1].y > 0) --character[1].y;
			break;
		case '5':
			if (character[1].y < window_size_d) ++character[1].y;
			break;
		case VK_RSHIFT:

			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		//mem2dc = CreateCompatibleDC(mem1dc);
		//oldBit1 = (HBITMAP)SelectObject(memdc, hBit1);
		SelectObject(memdc, hBit1);


		DeleteDC(memdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBit1);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}