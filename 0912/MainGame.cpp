#include "MainGame.h"


void MainGame::Init()
{
	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);

	mousePosX = 0;
	mousePosY = 0;
	clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	playerTank.Init();

	levelManager.Init();
	levelManager.SpawnTank();
	levelManager.SetPlayer(playerTank);
	
	POINTFLOAT pos { WIN_SIZE_X / 2, 400 };

}

void MainGame::Update()
{
	playerTank.Update();
	levelManager.Update(playerTank.GetPos(), playerTank);
	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	wsprintf(text, "MousePosX : %d", mousePosX);
	TextOut(hdc, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", mousePosY);
	TextOut(hdc, 200, 40, text, strlen(text));

	levelManager.Render(hdc);
	playerTank.Render(hdc);

}

void MainGame::Release()
{
	playerTank.Release();


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
			playerTank.Fire();
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
