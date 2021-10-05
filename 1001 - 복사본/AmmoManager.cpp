#include "AmmoManager.h"
#include "Ammo.h"
#include "GameObject.h"

void AmmoManager::Init()
{
	owner = nullptr;

	//아모 생성
	if (state == 1)
	{
		ammoMaxCount = 300;
		vecAmmo.resize(ammoMaxCount);
		for (itAmmo = vecAmmo.begin(); itAmmo<vecAmmo.end(); itAmmo++)
		{
			(*itAmmo) = new Ammo;
			(*itAmmo)->Init();
		}
	}
	else if (state == 2)
	{
		ammoMaxCount = 3;
		vecAmmo.resize(ammoMaxCount);
		for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo++)
		{
			(*itAmmo) = new Ammo;
			(*itAmmo)->Init();
		}
	}
	else if (state == 3)
	{
		ammoMaxCount = 9;
		vecAmmo.resize(ammoMaxCount);
		for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo++)
		{
			(*itAmmo) = new Ammo;
			(*itAmmo)->Init();
		}
	}
	else if (state == 4)
	{
		ammoMaxCount = 10;
		vecAmmo.resize(ammoMaxCount);
		for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo++)
		{
			(*itAmmo) = new Ammo;
			(*itAmmo)->Init();
		}
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

	if (state == 1) // 보스 패턴 1
	{
		timer++;
		if (timer <= 160 && timer>=40)
		{
			for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo+=2)
			{
				if ((*itAmmo)->GetIsFire() || (*(itAmmo+1))->GetIsFire()) continue;
				(*itAmmo)->SetIsFire(true);
				(*itAmmo)->SetPos(owner->GetPos());
				(*itAmmo)->SetMoveAngle(DEGREE_TO_RADIAN( 30 * (degreeIndex++ % 12) ) + degreeIndex*3 );
				itAmmo++;
				(*itAmmo)->SetIsFire(true);
				(*itAmmo)->SetPos(owner->GetPos());
				(*itAmmo)->SetMoveAngle(DEGREE_TO_RADIAN(30 * (degreeIndex++ % 12)) + degreeIndex*3);
				break;
			}
		}

		else if(timer>=190)
		{
			for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo ++)
			{
				if ((*itAmmo)->GetIsFire() || (*(itAmmo + 1))->GetIsFire()) continue;
				(*itAmmo)->SetIsFire(true);
				(*itAmmo)->SetPos(POINTFLOAT{ (float)(rand() % WIN_SIZE_X), 0.0f });
				(*itAmmo)->SetMoveAngle(DEGREE_TO_RADIAN(270));

				break;
			}
		}

		if (timer == 300)
			timer = 0;

	}
	else if (state == 2) // 잡몹 패턴 2
	{
		for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo ++)
		{
			if ((*itAmmo)->GetIsFire()) continue;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle( atan2(owner->GetPos().y -target->GetPos().y, -(owner->GetPos().x - target->GetPos().x)) );
			break;
		}
	}
	else if (state == 3) // 잡몹 패턴 2
	{
		for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo+=3)
		{
			if ((*itAmmo)->GetIsFire() || (*(itAmmo+1))->GetIsFire() || (*(itAmmo+2))->GetIsFire()) continue;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x)));
			itAmmo++;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x-30)));
			itAmmo++;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x + 30)));
			break;
		}
	}
	else if (state == 4) // 잡몹 패턴 2
	{
		for (itAmmo = vecAmmo.begin(); itAmmo < vecAmmo.end(); itAmmo += 5)
		{
			if ((*itAmmo)->GetIsFire() || (*(itAmmo + 1))->GetIsFire() || (*(itAmmo + 2))->GetIsFire() || (*(itAmmo + 3))->GetIsFire() || (*(itAmmo + 4))->GetIsFire()) continue;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x))+DEGREE_TO_RADIAN(-144));
			itAmmo++;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x ))+ DEGREE_TO_RADIAN(-72));
			itAmmo++;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x ))+ DEGREE_TO_RADIAN(0));
			itAmmo++;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x ))+ DEGREE_TO_RADIAN(72));
			itAmmo++;
			(*itAmmo)->SetIsFire(true);
			(*itAmmo)->SetPos(owner->GetPos());
			(*itAmmo)->SetMoveAngle(atan2(owner->GetPos().y - target->GetPos().y, -(owner->GetPos().x - target->GetPos().x ))+ DEGREE_TO_RADIAN(144));
			break;
		}
	}
}
