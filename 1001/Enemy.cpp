#include "Enemy.h"
#include "Image.h"
#include "AmmoManager.h"

void Enemy::Init()
{

	fireDelay = rand() % 100;
	fireTimer = 0;

	ImageManager::GetSingleton()->AddImage("Image/ufo.bmp", 530, 32,10,1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("Image/ufo.bmp");
	if (image == nullptr)
	{
		return;
	}

	pos.x = WIN_SIZE_X / 2;
	pos.y = 100;
	moveSpeed = 1.0f;
	bodySize = 53;

	elapsedCount = 0;

	ammoManager = new AmmoManager;
	ammoManager->Init();

	ammoManager->SetOwner(this);
}

void Enemy::Update()
{
	elapsedCount++;
	if (elapsedCount >= 10)
	{
		image->SetCurrFrameX(image->GetCurrFrameX()+1);
		if (image->GetCurrFrameX() >= image->GetMaxFrameX())
		{
			image->SetCurrFrameX(0);
		}
		elapsedCount = 0;
	}


	//Ammo
	/*
		1. 랜덤시간마다 미사일을 한발 씩 발사하도록 구현
		2. 딜레이 없이 30발 연속 발사
	*/

	fireTimer++;
	if (fireTimer >= fireDelay)
	{
		ammoManager->fire();
		fireTimer = 0;
		fireDelay = rand() % 100;
	}
	ammoManager->Update();

}

void Enemy::Render(HDC hdc)
{
	image->Render(hdc,pos.x,pos.y, image->GetCurrFrameX(),image->GetCurrFrameY());
	ammoManager->Render(hdc);
}

void Enemy::Release()
{
}
