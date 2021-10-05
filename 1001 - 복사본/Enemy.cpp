#include "Enemy.h"
#include "Image.h"
#include "AmmoManager.h"

void Enemy::Init()
{
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
	SetState();
	ammoManager->SetState(this->state);
	ammoManager->Init();

	ammoManager->SetTarget(target);

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


	if(this->pos.y>=0)
	{
		fireTimer++;
		if (fireTimer >= fireDelay)
		{
			ammoManager->fire();
			fireTimer = 0;
			SetFireDelay();
		}
	}
	ammoManager->Update();

	EnemyMove();
}

void Enemy::Render(HDC hdc)
{
	image->Render(hdc,pos.x,pos.y, image->GetCurrFrameX(),image->GetCurrFrameY());
	ammoManager->Render(hdc);
}

void Enemy::Release()
{
}

void EnemyState1::EnemyMove()
{
	if (this->pos.y >= 0) moveTimer++;

	if (this->pos.y <= 200 && !isReach)
	{
		this->pos.y += 2;
		if (this->pos.y >= 200) isReach = true;
	}
	else if (moveTimer <=310 &&isReach)
	{
		this->pos.y -= cos(DEGREE_TO_RADIAN(this->pos.x ) * 1.1 );
		this->pos.x += 2;
	}
	else if (moveTimer > 310 && isReach)
	{
		this->pos.y += 2;
	}
}

void EnemyState2::EnemyMove()
{
	if (this->pos.y >= 0) moveTimer++;

	if (this->pos.y <= 200 && !isReach)
	{
		this->pos.y += 2;
		if (this->pos.y >= 200) isReach = true;
	}
	else if (moveTimer <= 310 && isReach)
	{
		this->pos.y -= cos(DEGREE_TO_RADIAN(this->pos.x) * 1.1);
		this->pos.x -= 2;
	}
	else if (moveTimer > 310 && isReach)
	{
		this->pos.y += 2;
	}
}

void EnemyState3::EnemyMove()
{
	if (this->pos.y >= 0) moveTimer++;

	if (this->pos.y <= 300 && !isReach)
	{
		this->pos.y += 2;
		if (this->pos.y >= 300) isReach = true;
	}
	else if (isReach)
	{
		this->pos.y += 2;
		this->pos.x -= abs(sin(DEGREE_TO_RADIAN(this->pos.y) * 1.1));
	}
}

void EnemyState4::EnemyMove()
{
	if (this->pos.y >= 0) moveTimer++;

	if (this->pos.y <= 300 && !isReach)
	{
		this->pos.y += 2;
		if (this->pos.y >= 300) isReach = true;
	}
	else if (isReach)
	{
		this->pos.y += 2;
		this->pos.x += abs(sin(DEGREE_TO_RADIAN(this->pos.y) * 1.1));
	}
}

void EnemyState5::EnemyMove()
{
	if (this->pos.y >= 0) moveTimer++;

	if (this->pos.y <= 200 && !isReach)
	{
		this->pos.y += 2;
		if (this->pos.x > randX) this->pos.x--;
		else if (this->pos.x < randX) this->pos.x++;

		if (this->pos.y >= 200) isReach = true;
	}
	else if (isReach && moveTimer>=200)
	{
		this->pos.y -= 2;
	}
}


void Boss1::EnemyMove()
{
	if (this->pos.y <= 150)
	{
		this->pos.y += 2;
	}
}
