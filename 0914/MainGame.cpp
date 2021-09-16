#include "MainGame.h"
#include "SingleTon.h"
#include "KeyManager.h"


void MainGame::Init()
{


	Singleton<KeyManager>::GetSingleton()->Init();

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 50, NULL);

	mousePosX = 0;
	mousePosY = 0;
	clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	playerTank.Init(TankType::Player);
	playerTank.SetMoveSpeed(10.0f);

	enemyTank.Init(TankType::Enemy);
	POINTFLOAT pos { WIN_SIZE_X - 50, 400 };
	enemyTank.SetPos(pos);
	enemyTank.SetBarrelAngle(DEGREE_TO_RADIAN(270.0f));
	enemyTank.SetMoveSpeed(8.0f);

	playerTank.SetTarget(&enemyTank);

	if (!SUCCEEDED(imgWonBin.Init("../Image/bin.bmp", 1300, 933))) {
		cout << "파일 로드에 실패 했다." << endl;
	}
}

void MainGame::Update()
{
	playerTank.Update();
	enemyTank.Update();

	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	wsprintf(text, "MousePosX : %d", mousePosX);
	TextOut(hdc, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", mousePosY);
	TextOut(hdc, 200, 40, text, strlen(text));

	imgWonBin.Render(hdc, 0, 0);

	playerTank.Render(hdc);

	enemyTank.Render(hdc);
}

void MainGame::Release()
{
	playerTank.Release();

	enemyTank.Release();

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			InvalidateRect(g_hWnd, NULL, true);
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			playerTank.RotateBarrelAngle(1.0f);
			InvalidateRect(g_hWnd, NULL, true);
			break;
		case VK_RIGHT:
			playerTank.RotateBarrelAngle(-1.0f);
			InvalidateRect(g_hWnd, NULL, true);
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);

		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
