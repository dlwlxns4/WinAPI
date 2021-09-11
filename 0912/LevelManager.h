#pragma once
#include <vector>
#include "Config.h"
#include "GameObject.h"
#include "Tank.h"
#include <vector>

using namespace std;
class LevelManager  	
{
public:
	int level;
	vector<Tank> tank;
	Tank Player;

public:
	void SpawnTank();
	void Init();
	void Render(HDC hdc);
	void Update(POINTFLOAT pos, Tank& playerTank);
	void SetPlayer(Tank player) { this->Player = player; }
};

