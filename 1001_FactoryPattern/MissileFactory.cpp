#include "MissileFactory.h"
#include "Missile.h"

void MissileFactory::NewMissile()
{
	Missile* missile = CreateMissile();
	vecMissiles.push_back(missile);

	missile->Notice();
}

MissileFactory::~MissileFactory()
{
	for (vector<Missile*>::iterator it = vecMissiles.begin();
		it != vecMissiles.end();
		it++)
	{
		delete (*it);		// Missile
	}
	vecMissiles.clear();
}

Missile* NormalMissileFactory::CreateMissile()
{
	return new NormalMissile;
}

NormalMissileFactory::~NormalMissileFactory()
{
}

Missile* HommingMissileFactory::CreateMissile()
{
	return new HommingMissile;
}

HommingMissileFactory::~HommingMissileFactory()
{
}

Missile* FireworkMissileFactory::CreateMissile()
{
	return new FireworkMissile;
}

FireworkMissileFactory::~FireworkMissileFactory()
{
}
