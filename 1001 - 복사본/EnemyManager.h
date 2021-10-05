#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "GameObject.h"

class Enemy;
class EnemyFactory;
class EnemyManager : public GameEntity
{
private:
	vector<Enemy*> vecEnemys;
	vector<Enemy*>::iterator itEnemys;

	EnemyFactory* ef[10];

	//target
	GameObject* target;

	int stateTimer;

	int enemyMaxCount;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();


	void EnemyState1Spawn();
	void EnemyState2Spawn();
	void EnemyState3Spawn();
	void EnemyState4Spawn();
	void EnemyState5Spawn();
	void Boss1Spawn();

	void AddEnemy(float posX, float posY);
	inline void SetTarget(GameObject* target) { this->target = target; };

};

