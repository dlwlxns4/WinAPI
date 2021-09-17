#include "Iori.h"
#include "Image.h"
#include "KeyManager.h"

void Iori::Init()
{
	img = new Image;
	img->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255,0,255));

	frameX = frameY = 0;
	elpasedCount = 0;
	moveSpeed = 10.0f;
}

void Iori::Init(int posX, int posY, bool isMoveRight)
{
	this->pos.x = posX, this->pos.y = posY;

	img = new Image;
	img->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255));

	frameX = frameY = 0;
	elpasedCount = 0;
	moveSpeed = 10.0f;

	isMoveRight ? moveDir = MoveDir::Right : moveDir = MoveDir::Left;


}

void Iori::Update()
{

	// 실습1. 뒤로 움직이기 
	// 과제. 팀작업 때 쓸 리소스 찾아보기 (제자리 서있기, 앞으로 이동, 뒤로 이동, 작은 손/발, 큰 손/발, 피격(맞 았을 때)


	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
		elpasedCount++;
		if (elpasedCount == 5) {
			frameX != 8 ? frameX++ : frameX = 0;
			(this->pos.x) += moveSpeed;
			elpasedCount = 0;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
		elpasedCount++;
		if (elpasedCount == 5) {
			frameX != 0 ? frameX-- : frameX = 8;
			(this->pos.x) -= moveSpeed;
			elpasedCount = 0;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT) || KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) ){
		frameX = 0;
	}

}

void Iori::Update2()
{
	if (moveDir == MoveDir::Left) {
		(this->pos.x) -= moveSpeed;
	}
	else if(moveDir == MoveDir::Right){
		(this->pos.x) += moveSpeed;
	}

	rect.left = pos.x-34;
	rect.top = pos.y-52;
	rect.right = pos.x + 34;
	rect.bottom = pos.y + 52;
}

void Iori::Render(HDC hdc)
{
	if (img) {
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		img->Render(hdc, pos.x, pos.y, frameX, frameY);
	}
}

void Iori::Release()
{
	if (img) {
		delete img;
	}
}

void Iori::IsCollision()
{
}


