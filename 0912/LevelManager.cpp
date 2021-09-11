#include "LevelManager.h"

#include <time.h>
void LevelManager::SpawnTank()
{
	srand(time(NULL));
	switch (level) {
	case 1:
		for (int i = 0; i < 3; i++) {
			
			
			Tank addTank;
			POINTFLOAT pos;
			pos.x = rand() % 1000 + 100;
			pos.y = 100;

			addTank.Init();
			
			if (i < 1) {
				addTank.HP = 3;
			}
			
			addTank.SetMoveSpeed(8.0f);
			addTank.SetShapePosition(pos);
			tank.push_back(addTank);
		}
		break;
	case 2:
		for (int i = 0; i < 6; i++) {


			Tank addTank;
			POINTFLOAT pos;
			pos.x = rand() % 1000 + 100;
			pos.y = 100;

			addTank.Init();


			if (i < 2) {
				addTank.HP = 3;
			}
			addTank.SetMoveSpeed(8.0f);
			addTank.SetShapePosition(pos);
			tank.push_back(addTank);
		}
		break;
	case 3:
		for (int i = 0; i < 9; i++) {


			Tank addTank;
			POINTFLOAT pos;
			pos.x = rand() % 1000 + 100;
			pos.y = 100;

			addTank.Init();


			if (i < 3) {
				addTank.HP = 3;
			}
			addTank.SetMoveSpeed(8.0f);
			addTank.SetShapePosition(pos);
			tank.push_back(addTank);
		}
		break;
	}
}

void LevelManager::Init()
{
	level = 1;
}

void LevelManager::Render(HDC hdc)
{
	switch (level) {
	case 1:
		for (int i = 0; i < tank.size(); i++) {
			if(tank[i].isAlive)
				tank[i].EnemyRender(hdc);
		}
		break;
	case 2:
		for (int i = 0; i < tank.size(); i++) {
			if (tank[i].isAlive)
				tank[i].EnemyRender(hdc);
		}
		break;
	case 3:
		for (int i = 0; i < tank.size(); i++) {
			if (tank[i].isAlive)
				tank[i].EnemyRender(hdc);
		}
		break;
	}
}

void LevelManager::Update(POINTFLOAT pos, Tank &playerTank) 
{

	playerTank.ammo.CheckCollision(tank);
	
	switch (level) {
	case 1:

		for (int i = 0; i < tank.size(); i++) {
				tank[i].ChaserPlayer(pos);
		}
		if (tank.empty()) {
			level++;
			SpawnTank();
		}
		break;
	case 2:

		for (int i = 0; i < tank.size(); i++) {
			tank[i].ChaserPlayer(pos);
		}
		if (tank.empty()) {
			level++;
			SpawnTank();
		}
		break;
	case 3:

		for (int i = 0; i < tank.size(); i++) {
			tank[i].ChaserPlayer(pos);
		}
		if (tank.empty()) {
			level++;
		}
		break;
	}
}
