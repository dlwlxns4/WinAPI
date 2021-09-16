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

	// �ǽ�1. �ڷ� �����̱� 
	// ����. ���۾� �� �� ���ҽ� ã�ƺ��� (���ڸ� ���ֱ�, ������ �̵�, �ڷ� �̵�, ���� ��/��, ū ��/��, �ǰ�(�� ���� ��)


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
