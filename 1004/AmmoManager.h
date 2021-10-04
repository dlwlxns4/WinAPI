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
	
	
	GameObject* owner; // 상속을 통한 업캐스팅 사용
	

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void fire();
	inline void SetOwner(GameObject* owner) { this->owner = owner; };
};

