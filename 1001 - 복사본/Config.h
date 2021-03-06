#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <vector>

#include <map>


using namespace std;

#pragma comment(lib, "winmm.lib")

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	600
#define WIN_SIZE_Y	800

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
#include "Singleton.h"


extern HWND g_hWnd;
extern HINSTANCE g_hInstance;