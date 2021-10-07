#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	600
#define WIN_SIZE_Y	800
#define TILEMAPTOOL_SIZE_X	1500
#define TILEMAPTOOL_SIZE_Y	800

#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

enum MoveDir { Left, Right, Up, Down };
enum class TankType { Player, Enemy };


#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;



//타일 관련
#define TILE_SIZE	32
#define TILE_COUNT_X	20
#define TILE_COUNT_Y	20
#define SAMPLE_TILE_COUNT_X	20
#define SAMPLE_TILE_COUNT_Y	9

enum class Terrain { Earth, Wall, Water, Grass, BreakableWall, End };

typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
} SAMPLE_TILE_INFO;

typedef struct tagTile
{
	Terrain terrain;
	RECT rc;
	//image
	// sample tile의 아이디 (프레임 X, 프레임 Y)
	int frameX, frameY;
} TILE_INFO;

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
	TILE_INFO *tileInfo;
	int saveIndex;
	int loadIndex;
} ARGUMENT_PTR, *LPARGUMENT_PTR;