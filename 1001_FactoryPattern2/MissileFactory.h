#pragma once
#include <vector>

using namespace std;

class Missile;
class MissileFactory
{
	vector<Missile*>	vecMissiles;
	virtual Missile* CreateMissile() = 0;

public:
	void NewMissile();

	MissileFactory() {}
	~MissileFactory();
};

class NormalMissileFactory : public MissileFactory
{
	virtual Missile* CreateMissile() override;

public:
	NormalMissileFactory() {}
	~NormalMissileFactory();
};

class HommingMissileFactory : public MissileFactory
{
	virtual Missile* CreateMissile() override;

public:
	HommingMissileFactory() {}
	~HommingMissileFactory();
};

class FireworkMissileFactory : public MissileFactory
{
	virtual Missile* CreateMissile() override;

public:
	FireworkMissileFactory() {}
	~FireworkMissileFactory();
};