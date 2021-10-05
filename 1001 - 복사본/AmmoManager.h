#include "Config.h"
#include "GameEntity.h"

#pragma once
class Ammo;
class GameObject;
class AmmoManager : public GameEntity
{
private:
	vector<Ammo*> vecAmmo;
	vector<Ammo*>::iterator itAmmo;

	int ammoMaxCount;
	
	GameObject* target;
	GameObject* owner; // 상속을 통한 업캐스팅 사용
	int state;

	int degreeIndex = 0;
	int timer = 0;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void fire();
	inline void SetOwner(GameObject* owner) { this->owner = owner; };
	inline void SetState(int state) { this->state = state; };
	inline void SetTarget(GameObject* target) { this->target = target; };
};

