#pragma once
#include "GameEntity.h"

class Tank;
class Image;
class Enemy;
class EnemyManager;
class BattleScene : public GameEntity
{
private:
	// ��ũ (�÷��̾�)
	Tank* rocket;
	// ��
	EnemyManager* enemyManager;
	// ��� �̹���
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();


};

