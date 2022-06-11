#pragma once

//헤더
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

#pragma comment(lib, "msimg32.lib")

//정의
#define	WINSIZE_W	800
#define WINSIZE_H	600

#define PI			3.141592

#define OBJ_TILE_W	40
#define OBJ_TILE_H	40
#define OBJ_TREE_W	40
#define OBJ_TREE_H	70
#define OBJ_HOUSE_W	40
#define OBJ_HOUSE_H	53
#define OBJ_BLOCK_W 40
#define OBJ_BLOCK_H 44

#define CHA_SHEET_W	200
#define CHA_SHEET_H	360
#define CHA_MOVE_W	50
#define CHA_MOVE_H	60
#define CHA_TRAP_W	60		//물풍선에 갇혔을 경우
#define CHA_TRAP_H	60
#define CHA_POP_W	65		//물풍선이 터질 경우
#define CHA_POP_H	60
#define CHA_COLL_W	40		//캐릭터 충돌 렉트
#define CHA_COLL_H	40

#define STAGE_START_X	60		//스테이지1 맵 시작좌표
#define STAGE_START_Y	81		//맵 y좌표 81
#define STAGE_WIDTH		13		//스테이지1 맵 칸의 수
#define STAGE_HEIGHT	11
#define STAGE_END_X		STAGE_START_X + OBJ_TILE_W * STAGE_WIDTH
#define STAGE_END_Y		STAGE_START_Y + OBJ_TILE_H * STAGE_HEIGHT
#define PLAYER_X		60 		
#define PLAYER_Y		60
#define PLAYER_END_X	STAGE_END_X - CHA_MOVE_W
#define PLAYER_END_Y	STAGE_END_Y - 65
#define BLOCK_MAX		STAGE_WIDTH * STAGE_HEIGHT

#define BOMB_W			40
#define BOMB_H			44
#define BOMB_LINE_W		40
#define BOMB_LINE_H		40
#define BOMB_POWER_MAX	10

#define PLAYER_SPAWN_0_X PLAYER_X
#define PLAYER_SPAWN_0_Y PLAYER_Y
#define PLAYER_SPAWN_1_X PLAYER_X
#define PLAYER_SPAWN_1_Y PLAYER_END_Y
#define PLAYER_SPAWN_2_X PLAYER_END_X
#define PLAYER_SPAWN_2_Y PLAYER_Y
#define PLAYER_SPAWN_3_X PLAYER_END_X
#define PLAYER_SPAWN_3_Y PLAYER_END_Y

#define COLOR	RGB(100, 100, 100)
#define SAFE_DELETE(p)		{ if((p)){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARR(p)	{ if((p)){ delete[] (p); (p) = NULL; } }

//전역변수
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;

extern int GAMESTATE;
extern int STATE_1P;
extern int STATE_2P;
extern int PLAYER_1P;
extern int PLAYER_2P;

extern POINT MOUSE_POS;
extern POINT PLAYER_1P_POS;
extern POINT PLAYER_2P_POS;

enum
{
	OPENING,
	ROOM,
	STAGE
};
enum
{
	DAO,
	DIGENIE,
	BAZZI,
	UNI,
	RANDOM
};
enum
{
	STAND,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIE,
	BUBBLE,
	POP
};
