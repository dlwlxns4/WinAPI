#pragma once
#include "Config.h"
#include "GameObject.h"

class AmmoManager;
class Enemy : public GameObject
{
private:
	int elapsedCount;
	AmmoManager* ammoManager;

	int fireDelay;
	int fireTimer;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

