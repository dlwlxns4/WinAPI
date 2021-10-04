#include "MainGame.h"
#include "Image.h"

#include "TitleScene.h"
#include "BattleScene.h"
#include "LoadingScene.h"


HRESULT MainGame::Init()
{
	srand((unsigned int)time(NULL));
	//Singleton<int> singleton1;
	//singleton1.ProcessInputKey();
	//Singleton<KeyManager>::GetSingleton()->Init();

	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("타이틀씬", new TitleScene());
	SceneManager::GetSingleton()->AddScene("전투씬", new BattleScene());
	SceneManager::GetSingleton()->AddLoadingScene("로딩씬", new LoadingScene());

	SceneManager::GetSingleton()->ChangeScene("타이틀씬");

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	mousePosX = 0;
	mousePosY = 0;
	//clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);





	return S_OK;
}

void MainGame::Update()
{
	// 현재시간

	// 현재 시간 - 이전 시간 = 경과 시간

	TimerManager::GetSingleton()->Update();

	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);

	// 이전 시간 = 현재 시간
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	wsprintf(text, "MousePosX : %d", mousePosX);
	TextOut(hBackBufferDC, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", mousePosY);
	TextOut(hBackBufferDC, 200, 40, text, strlen(text));

	SceneManager::GetSingleton()->Render(hBackBufferDC);


	//Timer
	TimerManager::GetSingleton()->Render(hBackBufferDC);

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);
	TimerManager::GetSingleton()->Release();
	TimerManager::GetSingleton()->ReleaseSingleton();


	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();


	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();


	SceneManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->ReleaseSingleton();

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
