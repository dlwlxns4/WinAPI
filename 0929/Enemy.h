#pragma once
#include "Config.h"
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	int elapsedCount;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

