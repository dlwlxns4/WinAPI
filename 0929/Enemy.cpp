#include "Enemy.h"
#include "Image.h"

void Enemy::Init()
{
	image = new Image;
	image->Init("Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));

	pos.x = WIN_SIZE_X / 2;
	pos.y = 100;
	moveSpeed = 1.0f;
	bodySize = 53;

	elapsedCount = 0;
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
}

void Enemy::Render(HDC hdc)
{
	image->Render(hdc,pos.x,pos.y, image->GetCurrFrameX(),image->GetCurrFrameY());
}

void Enemy::Release()
{
	SAFE_RELEASE(image);
}
