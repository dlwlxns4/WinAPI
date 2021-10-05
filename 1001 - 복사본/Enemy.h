#pragma once
#include "Config.h"
#include "GameObject.h"

class AmmoManager;
class Enemy : public GameObject
{
protected:
	int elapsedCount;
	AmmoManager* ammoManager;

	int fireDelay;
	int fireTimer;
	GameObject* target;

public:
	int state;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	inline void SetTarget(GameObject* target) { this->target = target; };

	virtual void EnemyMove() = 0;
	virtual inline void SetState() = 0;
	virtual inline void SetFireDelay()=0;
	
};

class Boss1 : public Enemy
{
public:
	virtual void EnemyMove();
	virtual inline void SetState() { this->state = 1; }; 
	virtual inline void SetFireDelay() { fireDelay = 2; };
	virtual inline void SetFireDelay(int fireDelay) { this->fireDelay = fireDelay; };
	
};

class EnemyState1 : public Enemy
{
	bool isReach = false;
	int moveTimer = 0;

public:
	virtual void EnemyMove();
	virtual inline void SetState() { this->state = 2; };
	virtual inline void SetFireDelay() { fireDelay = 100; };
	virtual inline void SetFireDelay(int fireDelay) { this->fireDelay = fireDelay; };
};

class EnemyState2 : public Enemy
{
	bool isReach = false;
	int moveTimer = 0;

public:
	virtual void EnemyMove();
	virtual inline void SetState() { this->state = 2; };
	virtual inline void SetFireDelay() { fireDelay = 100; };
	virtual inline void SetFireDelay(int fireDelay) { this->fireDelay = fireDelay; };
};

class EnemyState3 : public Enemy
{
	bool isReach = false;
	int moveTimer = 0;

public:
	virtual void EnemyMove();
	virtual inline void SetState() { this->state = 3; };
	virtual inline void SetFireDelay() { fireDelay = 150; };
	virtual inline void SetFireDelay(int fireDelay) { this->fireDelay = fireDelay; };
};

class EnemyState4 : public Enemy
{
	bool isReach = false;
	int moveTimer = 0;

public:
	virtual void EnemyMove();
	virtual inline void SetState() { this->state = 3; };
	virtual inline void SetFireDelay() { fireDelay = 150; };
	virtual inline void SetFireDelay(int fireDelay) { this->fireDelay = fireDelay; };
};

class EnemyState5 : public Enemy
{
	int randX = rand() % 600;
	bool isReach = false;
	int moveTimer = 0;

public:
	virtual void EnemyMove();
	virtual inline void SetState() { this->state = 4; };
	virtual inline void SetFireDelay() { fireDelay = 10; };
	virtual inline void SetFireDelay(int fireDelay) { this->fireDelay = fireDelay; };
};
