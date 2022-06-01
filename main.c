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

typedef struct box {
	int left, right, top, bottom;
} box;

int collision(box A, box B);
int collision(box A, box B)
{
	if (A.left < B.left && A.right > B.left && A.top < B.bottom && A.top >= B.top) return 1;
	if (A.left < B.left && A.right > B.left && A.bottom > B.top && A.bottom <= B.bottom) return 1;
	if (A.left > B.right && A.right < B.right && A.top < B.bottom && A.top >= B.top) return 1;
	if (A.left > B.right && A.right < B.right && A.bottom > B.top && A.bottom <= B.bottom) return 1;
	return 0;
}

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

	int FrameX = GetSystemMetrics(SM_CXFRAME), FrameY = GetSystemMetrics(SM_CYFRAME), Caption = GetSystemMetrics(SM_CYCAPTION);

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
	box window = { 0,0,800,800 };
	AdjustWindowRect(&window, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(lpszClass, lpszWindowName, CW_USEDEFAULT, 100, 100, window_size_w, window_size_d, NULL, (HMENU)NULL, hInstance, NULL);
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
	int x, y, len, time, on, pop;
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
	HBRUSH hBrush, oldBrush;
	//HBITMAP oldBit1, oldBit2;
	static int bubble_num[2] = { 1,1 }, count1 = 0, count2 = 0;
	static int x = 0, y = 0, w = 330, h = 240, mx = 0, my = 0, mw = 1600, mh = 1200;
	static Character character[2];
	static Bubble bubble[14];
	static Object obj;
	static Item item;

	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		// character setting
		character[0].num_bubble = 1; character[1].num_bubble = 1;
		character[0].speed = 1; character[1].speed = 1;
		character[0].bubble_len = 1; character[1].bubble_len = 1;
		character[0].x = 0; character[0].y = 0; character[1].x = 39; character[1].y = 39;

		for (int i = 0; i < 14; i++)
		{
			bubble[i].on = 0; bubble[i].pop = 0;
			bubble[i].time = 0;
		}
		hBit1 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(101));
		break;
	case WM_TIMER:
	{ int pop_bubble = 0; 
		for (int i = 0; i < 14; i++)
		{
			if (bubble[i].pop == 1) {
				bubble[i].pop = 0;
				pop_bubble = i;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (bubble[i].on == 1) {

				bubble[i].time = (bubble[i].time + 1);
				if (bubble[i].time % 30 == 0) {
				if (i < 6) count1 -= 1;
				else count2 -= 1;
				bubble[i].on = 0; bubble[i].pop = 1;
				bubble[i].time = 0;
				InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}

		//collision
		box CharA = { character[0].x, character[0].x + 1, character[0].y, character[0].y + 1 };
		box CharB = { character[1].x, character[1].x + 1, character[1].y, character[1].y + 1 };
		box B_1 = { bubble[pop_bubble].x + 0, bubble[pop_bubble].x + 1, bubble[pop_bubble].y + 0, bubble[pop_bubble].y + 1 };
		box B_2 = { bubble[pop_bubble].x + 1, bubble[pop_bubble].x + 2, bubble[pop_bubble].y + 0, bubble[pop_bubble].y + 1 };
		box B_3 = { bubble[pop_bubble].x - 1, bubble[pop_bubble].x + 0, bubble[pop_bubble].y + 0, bubble[pop_bubble].y + 1 };
		box B_4 = { bubble[pop_bubble].x + 0, bubble[pop_bubble].x + 1, bubble[pop_bubble].y + 1, bubble[pop_bubble].y + 2 };
		box B_5 = { bubble[pop_bubble].x + 0, bubble[pop_bubble].x + 1, bubble[pop_bubble].y - 1, bubble[pop_bubble].y + 0 };

		if (collision(CharA, B_1) == 1) character[0].state = 1;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN: // MOVE: wasd // BUBBLE: f  0
		switch (wParam)
		{
			{
		case VK_LEFT:
			if ((character[0].x) * 20 > 0) character[0].x -= character[0].speed;
			break;
		case VK_RIGHT:
			if ((character[0].x + 1) * 20 < window_size_w) character[0].x += character[0].speed;
			break;
		case VK_UP:
			if ((character[0].y) * 20 > 0) character[0].y -= character[0].speed;
			break;
		case VK_DOWN:
			if ((character[0].y + 1) * 20 < window_size_d) character[0].y += character[0].speed;
			break;
		case 'D':
		case 'd':
			if ((character[1].x + 1) * 20 < window_size_w) character[1].x += character[1].speed;
			break;
		case 'W':
		case 'w':
			if ((character[1].y) * 20 > 0) character[1].y -= character[0].speed;
			break;
		case 'S':
		case 's':
			if ((character[1].y + 1) * 20 < window_size_d) character[1].y += character[0].speed;
			break;
		case 'a':
		case 'A':
			if ((character[1].x) * 20 > 0) character[1].x -= character[1].speed;
			break; }
		//case VK_LSHIFT:
		//	if (bubble_num[0] < character[0].num_bubble) {
		//		//++bubble_num[0]; 
		//		bubble[count1].x = character[0].x; bubble[count1].y = character[0].y;
		//		bubble[count1].time = 0; bubble[count1].on = 1;
		//		count1 = (count1 + 1) % character[0].num_bubble;
		//	}
		//	break;
		//case VK_RSHIFT:
		//	if (bubble_num[1] < character[1].num_bubble) {
		//		//++bubble_num[1]; 
		//		bubble[6+count2].x = character[1].x; bubble[6+count2].y = character[1].y;
		//		bubble[count2].time = 0; bubble[count2].on = 1;
		//		count2 = (count2 + 1) % character[1].num_bubble;
		//	}
		//	break;
		case 'f':
		case 'F':
			if (bubble_num[0] > count1) {
				//++bubble_num[0]; 
				bubble[count1].x = character[0].x; bubble[count1].y = character[0].y;
				bubble[count1].time = 0; bubble[count1].on = 1;
				count1 = (count1 + 1) % (character[0].num_bubble+1);
			}
			break;
		case 0x60:
			if (bubble_num[1] > count2) {
				//++bubble_num[1]; 
				bubble[6 + count2].x = character[1].x; bubble[6 + count2].y = character[1].y;
				bubble[6 + count2].time = 0; bubble[6 + count2].on = 1;
				count2 = (count2 + 1) % (character[1].num_bubble+1);
			}
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		//mem2dc = CreateCompatibleDC(mem1dc);
		//oldBit1 = (HBITMAP)SelectObject(memdc, hBit1);
		SelectObject(memdc, hBit1);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		for (int i = 0; i < bubble_num[0]; i++)
		{
			if (bubble[i].on == 1)
				Rectangle(hdc, bubble[i].x * 20, bubble[i].y * 20, (bubble[i].x + 1) * 20, (bubble[i].y + 1) * 20);
		}
		for (int i = 0; i < bubble_num[1]; i++)
		{
			if (bubble[6 + i].on == 1)
				Rectangle(hdc, bubble[6 + i].x * 20, bubble[6 + i].y * 20, (bubble[6 + i].x + 1) * 20, (bubble[6 + i].y + 1) * 20);
		}
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		for (int i = 0; i < bubble_num[0]; i++)
		{
			if (bubble[i].pop == 1)
			{
				Rectangle(hdc, (bubble[i].x) * 20, (bubble[i].y) * 20, (bubble[i].x + 1) * 20, (bubble[i].y + 1) * 20);
				Rectangle(hdc, (bubble[i].x + 1) * 20, (bubble[i].y) * 20, (bubble[i].x + 2) * 20, (bubble[i].y + 1) * 20);
				Rectangle(hdc, (bubble[i].x - 1) * 20, (bubble[i].y) * 20, (bubble[i].x) * 20, (bubble[i].y + 1) * 20);
				Rectangle(hdc, (bubble[i].x) * 20, (bubble[i].y + 1) * 20, (bubble[i].x + 1) * 20, (bubble[i].y + 2) * 20);
				Rectangle(hdc, (bubble[i].x) * 20, (bubble[i].y - 1) * 20, (bubble[i].x + 1) * 20, (bubble[i].y) * 20);
			}
		}
		for (int i = 0; i < bubble_num[1]; i++)
		{
			if (bubble[6 + i].pop == 1)
			{
				Rectangle(hdc, (bubble[6 + i].x) * 20, (bubble[6 + i].y) * 20, (bubble[6 + i].x + 1) * 20, (bubble[6 + i].y + 1) * 20);
				Rectangle(hdc, (bubble[6 + i].x + 1) * 20, (bubble[6 + i].y) * 20, (bubble[6 + i].x + 2) * 20, (bubble[6 + i].y + 1) * 20);
				Rectangle(hdc, (bubble[6 + i].x - 1) * 20, (bubble[6 + i].y) * 20, (bubble[6 + i].x) * 20, (bubble[6 + i].y + 1) * 20);
				Rectangle(hdc, (bubble[6 + i].x) * 20, (bubble[6 + i].y + 1) * 20, (bubble[6 + i].x + 1) * 20, (bubble[6 + i].y + 2) * 20);
				Rectangle(hdc, (bubble[6 + i].x) * 20, (bubble[6 + i].y - 1) * 20, (bubble[6 + i].x + 1) * 20, (bubble[6 + i].y) * 20);
			}
		}

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, character[0].x * 20, character[0].y * 20, (character[0].x + 1) * 20, (character[0].y + 1)* 20);
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush); 
		Rectangle(hdc, character[1].x * 20, character[1].y * 20, (character[1].x + 1) * 20, (character[1].y + 1) * 20);

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