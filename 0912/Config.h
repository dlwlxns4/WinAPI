#pragma once
#include <Windows.h>
#include <math.h>

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	1200
#define WIN_SIZE_Y	900

#define PI 3.14159265357989

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

enum MoveDir { Left, Right, Up, Down };
enum Level { ONE,TWO,THREE};

extern HWND g_hWnd;