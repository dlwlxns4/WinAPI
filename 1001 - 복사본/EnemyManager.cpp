#include "EnemyManager.h"
#include "Enemy.h"
#include "EnemyFactory.h"

void EnemyManager::Init()
{
	enemyMaxCount = 10;

	//데이터타입 : Enemy* 데이터를 10개를 생성, 삽입
	vecEnemys.reserve(50);

	ef[0] = new Boss1Factory;
	ef[1] = new Enemy1Factory;
	ef[2] = new Enemy2Factory;
	ef[3] = new Enemy3Factory;
	ef[4] = new Enemy4Factory;
	ef[5] = new Enemy5Factory;

	////데이터타입 : Enemy* 데이터 10개를 삽입할 수 있는 메모리만 확보
	stateTimer = 0;
}

void EnemyManager::Update()
{
	stateTimer++;
	
	if (stateTimer == 20) EnemyState1Spawn();
	else if (stateTimer == 350) EnemyState2Spawn();
	else if (stateTimer == 750) EnemyState3Spawn(), EnemyState4Spawn();
	else if (stateTimer == 1100) EnemyState5Spawn();
	else if (stateTimer == 1600) Boss1Spawn();


	for (itEnemys = vecEnemys.begin(); itEnemys < vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update();
	}


	//for (int i = 0; i < enemyMaxCount; i++)
	//{
	//	vecEnemys[i]->Update();
	//}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys < vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}

	/*for (int i = 0; i < enemyMaxCount; i++)
	{
		vecEnemys[i]->Render(hdc);
	}*/
}

void EnemyManager::Release()
{
	for (int i = 0; i < vecEnemys.size(); i++)
	{
		SAFE_RELEASE(vecEnemys[i]);
	}
}

void EnemyState1()
{

}

void EnemyManager::EnemyState1Spawn()
{
	for (int i = 0; i < 5; i++)
	{
		Enemy* newEnemy = ef[1]->CreateEnemy();
		newEnemy->SetTarget(target);
		newEnemy->Init();
		newEnemy->SetMoveSpeed(4.0f);
		newEnemy->SetState();
		newEnemy->SetPos(POINTFLOAT{ WIN_SIZE_X / 8.0f + i*15, -20.0f - i*30 });
		vecEnemys.push_back(newEnemy);
	}
}

void EnemyManager::EnemyState2Spawn()
{
	for (int i = 0; i < 5; i++)
	{
		Enemy* newEnemy = ef[2]->CreateEnemy();
		newEnemy->SetTarget(target);
		newEnemy->Init();
		newEnemy->SetMoveSpeed(4.0f);
		newEnemy->SetState();
		newEnemy->SetPos(POINTFLOAT{ WIN_SIZE_X-( WIN_SIZE_X / 8.0f + i * 15), -20.0f - i * 30 });
		vecEnemys.push_back(newEnemy);
	}
}

void EnemyManager::EnemyState3Spawn()
{
	for (int i = 0; i < 5; i++)
	{
		Enemy* newEnemy = ef[3]->CreateEnemy();
		newEnemy->SetTarget(target);
		newEnemy->Init();
		newEnemy->SetMoveSpeed(4.0f);
		newEnemy->SetState();
		newEnemy->SetPos(POINTFLOAT{ (WIN_SIZE_X / 6.0f), -20.0f - i * 30 });
		vecEnemys.push_back(newEnemy);
	}
}

void EnemyManager::EnemyState4Spawn()
{
	for (int i = 0; i < 5; i++)
	{
		Enemy* newEnemy = ef[4]->CreateEnemy();
		newEnemy->SetTarget(target);
		newEnemy->Init();
		newEnemy->SetMoveSpeed(4.0f);
		newEnemy->SetState();
		newEnemy->SetPos(POINTFLOAT{ WIN_SIZE_X - (WIN_SIZE_X / 6.0f), -20.0f - i * 30 });
		vecEnemys.push_back(newEnemy);
	}
}

void EnemyManager::EnemyState5Spawn()
{
	for (int i = 0; i < 10; i++)
	{
		Enemy* newEnemy = ef[5]->CreateEnemy();
		newEnemy->SetTarget(target);
		newEnemy->Init();
		newEnemy->SetMoveSpeed(4.0f);
		newEnemy->SetState();
		newEnemy->SetPos(POINTFLOAT{ rand()%WIN_SIZE_X+0.0f , -0.0f - rand()%700});
		vecEnemys.push_back(newEnemy);
	}
}


void EnemyManager::Boss1Spawn()
{
	Enemy* newEnemy = ef[0]->CreateEnemy();
	newEnemy->SetTarget(target);
	newEnemy->Init();
	newEnemy->SetMoveSpeed(4.0f);
	newEnemy->SetState();
	newEnemy->SetPos(POINTFLOAT{ WIN_SIZE_X / 2, -20 });
	vecEnemys.push_back(newEnemy);
}

void EnemyManager::AddEnemy(float posX, float posY)
{
}
