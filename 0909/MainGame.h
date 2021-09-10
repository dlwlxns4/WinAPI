#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Tank.h"
#include "Ammo.h"



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
	// �÷��̾ �߻��� �̻���
	Ammo playerAmmo;
	
	// ��ũ (�� AI)
	Tank enemyTank;
	// ���� �߻��� �̻���
	Ammo enemyAmmo;

public:
	void Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	void DrawRect(HDC hdc, int x, int y, int size);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

