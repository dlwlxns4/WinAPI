#pragma once
class Enemy;
class EnemyFactory
{
public:
	virtual Enemy* CreateEnemy() = 0;
};

class Enemy1Factory : public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy() override;
};

class Enemy2Factory : public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy() override;
};

class Enemy3Factory : public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy() override;
};

class Enemy4Factory : public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy() override;
};

class Enemy5Factory : public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy() override;
};


class Boss1Factory : public EnemyFactory 
{
public:
	virtual Enemy* CreateEnemy() override;
};

