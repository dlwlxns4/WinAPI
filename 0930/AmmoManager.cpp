#include "AmmoManager.h"
#include "Ammo.h"
#include "GameObject.h"

void AmmoManager::Init()
{
	ammoMaxCount = 30;
	owner = nullptr;

	//아모 생성
	vecAmmo.resize(ammoMaxCount);
	for (itAmmo = vecAmmo.begin(); itAmmo<vecAmmo.end(); itAmmo++)
	{
		(*itAmmo) = new Ammo;
		(*itAmmo)->Init();
	}
	
}

void AmmoManager::Update()
{

	for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo++)
	{
		(*itAmmo)->Update();
	}

}

void AmmoManager::Render(HDC hdc)
{
	for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo++)
	{
		(*itAmmo)->Render(hdc);
	}
}

void AmmoManager::Release()
{
	for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo++)
	{
		SAFE_RELEASE((*itAmmo));
	}
	vecAmmo.clear();
}

void AmmoManager::fire()
{
	if (!owner) return;

	for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo++)
	{
		if ((*itAmmo)->GetIsFire()) continue;
		(*itAmmo)->SetIsFire(true);
		(*itAmmo)->SetPos(owner->GetPos());
		(*itAmmo)->SetMoveAngle(DEGREE_TO_RADIAN(270.0f));
		break;
	}
}
