#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Tank.h"
#include "Ammo.h"

#define MOVE_SPEED	5

enum NemoType { Big_1, Big_2, Small_1, End };
enum MoveDir { Left, Right, Up, Down };

struct Nemo
{
	int posX, posY;
	int left, top, right, bottom;
	int size;
	MoveDir dir;
	bool isFire, isAlive;
};

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

	// 제어권 처리
	NemoType controlID;
	NemoType notControlID;

	Nemo nemos[NemoType::End];

	// 탱크 (플레이어)
	Tank playerTank;
	// 플레이어가 발사할 미사일
	Ammo playerAmmo;
	
	// 탱크 (적 AI)
	Tank enemyTank;
	// 적이 발사할 미사일
	Ammo enemyAmmo;

public:
	void Init();
	void Update();
	//void Render();			// 오버라이딩 : 상속 관계에서 부모클래스의 함수를 재정의
	void Render(HDC hdc);	// 오버로딩
	void Release();

	void InitNemos(Nemo* nemos);
	void DrawRect(HDC hdc, int x, int y, int size);
	void DrawNemos(HDC hdc, const Nemo* nemos);
	void SetNemoData(Nemo* nemo);
	bool IsCollision(Nemo nemo1, Nemo nemo2);
	void ProcessInputKey(WPARAM wParam, Nemo* nemos, NemoType& controlID, NemoType& notControlID);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

