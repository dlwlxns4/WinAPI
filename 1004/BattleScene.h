#pragma once
#include "GameEntity.h"

class Tank;
class Image;
class Enemy;
class EnemyManager;
class BattleScene : public GameEntity
{
private:
	// 탱크 (플레이어)
	Tank* rocket;
	// 적
	EnemyManager* enemyManager;
	// 배경 이미지
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	//void Render();			// 오버라이딩 : 상속 관계에서 부모클래스의 함수를 재정의
	void Render(HDC hdc);	// 오버로딩
	void Release();


};

