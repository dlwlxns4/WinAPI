#include "EnemyFactory.h"
#include "Enemy.h"

Enemy* Boss1Factory::CreateEnemy()
{
    return new Boss1;
}

Enemy* Enemy1Factory::CreateEnemy()
{
    return new EnemyState1;
}


Enemy* Enemy2Factory::CreateEnemy()
{
    return new EnemyState2;
}

Enemy* Enemy3Factory::CreateEnemy()
{
    return new EnemyState3;
}

Enemy* Enemy4Factory::CreateEnemy()
{
    return new EnemyState4;
}
Enemy* Enemy5Factory::CreateEnemy()
{
    return new EnemyState5;
}