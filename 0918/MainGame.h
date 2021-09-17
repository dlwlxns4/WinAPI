#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Tank.h"
#include "Ammo.h"
#include <vector>

class Image;
class Iori;
// �츮�� ������ ���� ����
class MainGame : public GameEntity
{
private:
	// Ÿ�̸�
	HANDLE hTimer;

	// UI
	char text[128];

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	// ��ũ (�÷��̾�)
	Tank playerTank;
	
	// ��ũ (�� AI)
	Tank enemyTank;

	// �����
	Image* backBuffer;

	// ��� �̹���
	Image* backGround;
	vector<vector<Iori>> *enemyIori;

public:
	void Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

//int MainGame::clickedMousePosX = 0;