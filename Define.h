#pragma once

#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

#define   WINSIZE_W   800
#define WINSIZE_H   600

#define PI         3.141592

#define OBJ_TILE_W   40
#define OBJ_TILE_H   40
#define OBJ_TREE_W   40
#define OBJ_TREE_H   70
#define OBJ_HOUSE_W   40
#define OBJ_HOUSE_H   53
#define OBJ_BLOCK_W 40
#define OBJ_BLOCK_H 44

#define STAGE_START_X   60      //½ºÅ×ÀÌÁö1 ¸Ê ½ÃÀÛÁÂÇ¥
#define STAGE_START_Y   81      //¸Ê yÁÂÇ¥ 81
#define STAGE_WIDTH      13      //½ºÅ×ÀÌÁö1 ¸Ê Ä­ÀÇ ¼ö
#define STAGE_HEIGHT   11
#define STAGE_END_X      STAGE_START_X + OBJ_TILE_W * STAGE_WIDTH
#define STAGE_END_Y      STAGE_START_Y + OBJ_TILE_H * STAGE_HEIGHT

COLORREF COLOR = RGB(0, 0, 0);
HWND g_hWnd; HINSTANCE g_hInst;