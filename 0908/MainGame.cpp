#include "MainGame.h"

void MainGame::Init()
{
	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);

	controlID = NemoType::Big_1;
	notControlID = NemoType::Big_2;

	mousePosX = 0;
	mousePosY = 0;
	clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	InitNemos(nemos);

	playerTank.Init();
	playerAmmo.Init();

	enemyTank.Init();
	enemyAmmo.Init();
}

void MainGame::Update()
{
	playerTank.Update();
	playerAmmo.Update();

	enemyTank.Update();
	enemyAmmo.Update();

	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	wsprintf(text, "MousePosX : %d", mousePosX);
	TextOut(hdc, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", mousePosY);
	TextOut(hdc, 200, 40, text, strlen(text));


	playerTank.Render(hdc);
	playerAmmo.Render(hdc);

	enemyTank.Render(hdc);
	enemyAmmo.Render(hdc);
}

void MainGame::Release()
{
	playerTank.Release();
	playerAmmo.Release();

	enemyTank.Release();
	enemyAmmo.Release();

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}

void MainGame::InitNemos(Nemo* nemos)
{
	nemos[NemoType::Big_1].posX = 150;
	nemos[NemoType::Big_1].posY = 550;
	nemos[NemoType::Big_1].size = 100;
	nemos[NemoType::Big_1].left = nemos[NemoType::Big_1].posX - (nemos[NemoType::Big_1].size / 2);
	nemos[NemoType::Big_1].right = nemos[NemoType::Big_1].left + nemos[NemoType::Big_1].size;
	nemos[NemoType::Big_1].top = nemos[NemoType::Big_1].posY - (nemos[NemoType::Big_1].size / 2);
	nemos[NemoType::Big_1].bottom = nemos[NemoType::Big_1].top + nemos[NemoType::Big_1].size;
	nemos[NemoType::Big_1].dir = MoveDir::Left;
	nemos[NemoType::Big_1].isFire = false;
	nemos[NemoType::Big_1].isAlive = true;

	nemos[NemoType::Big_2].posX = 350;
	nemos[NemoType::Big_2].posY = 150;
	nemos[NemoType::Big_2].size = 100;
	nemos[NemoType::Big_2].left = nemos[NemoType::Big_2].posX - (nemos[NemoType::Big_2].size / 2);
	nemos[NemoType::Big_2].right = nemos[NemoType::Big_2].left + nemos[NemoType::Big_2].size;
	nemos[NemoType::Big_2].top = nemos[NemoType::Big_2].posY - (nemos[NemoType::Big_2].size / 2);
	nemos[NemoType::Big_2].bottom = nemos[NemoType::Big_2].top + nemos[NemoType::Big_2].size;
	nemos[NemoType::Big_2].dir = MoveDir::Left;
	nemos[NemoType::Big_2].isFire = false;
	nemos[NemoType::Big_2].isAlive = true;

	nemos[NemoType::Small_1].posX = 150;
	nemos[NemoType::Small_1].posY = 550;
	nemos[NemoType::Small_1].size = 50;
	nemos[NemoType::Small_1].left = nemos[NemoType::Small_1].posX - (nemos[NemoType::Small_1].size / 2);
	nemos[NemoType::Small_1].right = nemos[NemoType::Small_1].left + nemos[NemoType::Small_1].size;
	nemos[NemoType::Small_1].top = nemos[NemoType::Small_1].posY - (nemos[NemoType::Small_1].size / 2);
	nemos[NemoType::Small_1].bottom = nemos[NemoType::Small_1].top + nemos[NemoType::Small_1].size;
	nemos[NemoType::Small_1].dir = MoveDir::Up;
	nemos[NemoType::Small_1].isFire = false;
	nemos[NemoType::Small_1].isAlive = true;
}

void MainGame::DrawRect(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x + size, y);
	LineTo(hdc, x, y);
}

void MainGame::DrawNemos(HDC hdc, const Nemo* nemos) /*const*/	// 멤버변수의 값을 변경하지 않겠다
{
	for (int i = 0; i < NemoType::End; i++)
	{
		if (nemos[i].isAlive)
		{
			DrawRect(hdc, nemos[i].left, nemos[i].top, nemos[i].size);
		}
	}
}

void MainGame::SetNemoData(Nemo* nemo)
{
	nemo->left = nemo->posX - (nemo->size / 2);
	nemo->top = nemo->posY - (nemo->size / 2);
	nemo->right = nemo->left + nemo->size;
	nemo->bottom = nemo->top + nemo->size;
}

bool MainGame::IsCollision(Nemo nemo1, Nemo nemo2)
{
	// 4가지 겹치지 않을 상황을 모두 확인할 필요가 있을 때
	if (nemo1.left > nemo2.right)	return false;
	if (nemo1.right < nemo2.left)	return false;
	if (nemo1.top > nemo2.bottom)	return false;
	if (nemo1.bottom < nemo2.top)	return false;

	return true;
}

void MainGame::ProcessInputKey(WPARAM wParam, Nemo* nemos, NemoType& controlID, NemoType& notControlID)
{
	switch (wParam)
	{
	case VK_UP:
		nemos[controlID].posY -= MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].bottom < nemos[NemoType::Small_1].bottom)
		{
			nemos[NemoType::Small_1].posY =
				nemos[controlID].bottom - (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	case VK_DOWN:
		nemos[controlID].posY += MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].top > nemos[NemoType::Small_1].top)
		{
			nemos[NemoType::Small_1].posY =
				nemos[controlID].top + (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	case VK_LEFT:
		nemos[controlID].posX -= MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].right < nemos[NemoType::Small_1].right)
		{
			nemos[NemoType::Small_1].posX =
				nemos[controlID].right - (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	case VK_RIGHT:
		nemos[controlID].posX += MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].left > nemos[NemoType::Small_1].left)
		{
			nemos[NemoType::Small_1].posX =
				nemos[controlID].left + (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	}

	// 큰 네모끼리 충돌확인
	if (IsCollision(nemos[controlID], nemos[notControlID]))
	{
		// 작은 네모의 위치를 옮긴다.
		nemos[NemoType::Small_1].posX = nemos[notControlID].posX;
		nemos[NemoType::Small_1].posY = nemos[notControlID].posY;

		SetNemoData(&nemos[NemoType::Small_1]);

		// 제어권도 옮긴다.
		controlID = controlID == NemoType::Big_1 ? NemoType::Big_2 : NemoType::Big_1;
		notControlID = notControlID == NemoType::Big_1 ? NemoType::Big_2 : NemoType::Big_1;
	}

	InvalidateRect(g_hWnd, NULL, true);
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
