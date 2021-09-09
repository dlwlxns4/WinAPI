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

	// ����� ó��
	NemoType controlID;
	NemoType notControlID;

	Nemo nemos[NemoType::End];

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

	void InitNemos(Nemo* nemos);
	void DrawRect(HDC hdc, int x, int y, int size);
	void DrawNemos(HDC hdc, const Nemo* nemos);
	void SetNemoData(Nemo* nemo);
	bool IsCollision(Nemo nemo1, Nemo nemo2);
	void ProcessInputKey(WPARAM wParam, Nemo* nemos, NemoType& controlID, NemoType& notControlID);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

