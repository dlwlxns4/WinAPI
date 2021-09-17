#pragma once
#include "GameObject.h"
#include "Config.h"
//#include "Image.h"			// 컴파일 관계가 복잡, 컴파일 시간이 오래 걸림

class Image;					// 포함관계
class Iori : public GameObject  // 상속관계
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

