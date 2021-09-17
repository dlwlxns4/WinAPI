#pragma once
#include "GameObject.h"
#include "Config.h"
//#include "Image.h"			// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;					// ���԰���
class Iori : public GameObject  // ��Ӱ���
{
private:
	Image* img;
	int frameX, frameY;
	int elpasedCount;
	
	MoveDir moveDir;

public:
	RECT rect;



public:
	void Init();
	void Init(int posX, int posY, bool isMoveRight);
	void Update();
	void Update2();
	void Render(HDC hdc);
	void Release();
	MoveDir GetMoveDir() { return moveDir; };
	void SetMoveDir(MoveDir moveDir) { this->moveDir = moveDir; };
	void IsCollision();
};

