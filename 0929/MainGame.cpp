#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Tank.h"
#include "Enemy.h"

void MainGame::Init()
{
	//Singleton<int> singleton1;
	//singleton1.ProcessInputKey();
	//Singleton<KeyManager>::GetSingleton()->Init();

	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton();


	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	mousePosX = 0;
	mousePosY = 0;
	//clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	rocket = new Tank;
	rocket->Init(TankType::Player);

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = new Enemy;
		enemy[i]->Init();
		POINTFLOAT pos{ 100.0f + (i % 5) * 100.0f, 100.0f + (i / 5) * 80.0f };
		enemy[i]->SetPos(pos);
	}

	//데이터타입 : Enemy* 데이터를 10개를 생성, 삽입
	vecEnemys.resize(10);
	for (int i = 0; i < 10; i++)
	{
		vecEnemys[i] = new Enemy;
		vecEnemys[i]->Init();
	}

	//데이터타입 : Enemy* 데이터 10개를 삽입할 수 있는 메모리만 확보
	vecEnemys.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		vecEnemys.push_back(new Enemy);
		vecEnemys[i]->Init();
	}


	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	// 배경 이미지
	backGround = new Image;
	if (!SUCCEEDED(backGround->Init("Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y)))
	{
		cout << "Image/bin.bmp 파일 로드에 실패했다." << endl;
	}


}

void MainGame::Update()
{
	rocket->Update();
	for (int i = 0; i < 10; i++)
	{
		enemy[i]->Update();
	}


	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	wsprintf(text, "MousePosX : %d", mousePosX);
	TextOut(hBackBufferDC, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", mousePosY);
	TextOut(hBackBufferDC, 200, 40, text, strlen(text));

	backGround->Render(hBackBufferDC);

	rocket->Render(hBackBufferDC);
	for (int i = 0; i < 10; i++)
	{
		enemy[i]->Render(hBackBufferDC);
	}
	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(backGround);
	SAFE_RELEASE(rocket);
	
	for (int i = 0; i < 10; i++)
	{
		SAFE_RELEASE(enemy[i]);
	}

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
			//playerTank.Fire();
			break;
		case VK_UP:
			//playerTank.Move(MoveDir::Up);
			break;
		case VK_DOWN:
			//playerTank.Move(MoveDir::Down);
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
