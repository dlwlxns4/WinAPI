#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Tank.h"
#include "Ammo.h"
#include "LevelManager.h"

// 우리가 구성할 게임 월드
class MainGame : public GameEntity
{
private:
	// 타이머
	HANDLE hTimer;

	// UI
	char text[128];

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;


	// 탱크 (플레이어)
	Tank playerTank;
	
	//
	Tank enemyTank;

	int score;


	LevelManager levelManager;

public:
	void Init();
	void Update();
	//void Render();			// 오버라이딩 : 상속 관계에서 부모클래스의 함수를 재정의
	void Render(HDC hdc);	// 오버로딩
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

