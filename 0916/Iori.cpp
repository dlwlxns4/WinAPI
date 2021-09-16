#include "Iori.h"
#include "Image.h"
#include "KeyManager.h"

void Iori::Init()
{
	img = new Image;
	img->Init("Image/Iori_walk.bmp", 612,104,true, RGB(255,0,255));

	frameX = frameY = 0;
	elpasedCount = 0;
}

void Iori::Update()
{

	// 실습1. 뒤로 움직이기 
	// 과제. 팀작업 때 쓸 리소스 찾아보기 (제자리 서있기, 앞으로 이동, 뒤로 이동, 작은 손/발, 큰 손/발, 피격(맞 았을 때)


	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
		elpasedCount++;
		if (elpasedCount == 5) {
			frameX != 8 ? frameX++ : frameX = 0;
			(this->pos.x) += 10;
			elpasedCount = 0;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
		elpasedCount++;
		if (elpasedCount == 5) {
			frameX != 0 ? frameX-- : frameX = 8;
			(this->pos.x) -= 10;
			elpasedCount = 0;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT) || KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) ){
		frameX = 0;
	}

}

void Iori::Render(HDC hdc)
{
	if (img) {
		img->Render(hdc, WIN_SIZE_X/2 +pos.x, WIN_SIZE_Y/2, frameX, frameY);
	}
}

void Iori::Release()
{
	if (img) {
		delete img;
	}
}
