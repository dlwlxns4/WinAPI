#include "Tank.h"



void Tank::Init()
{
	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = WIN_SIZE_Y - 50;

	bodySize = 50;
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	moveSpeed = 0.0f;

	barrelSize = 140.0f;
	barrelAngle = 90.0f * (PI / 180.0f);	// 각도의 단위 :	도 (degree) : 0 ~ 360
											//	(radian) : 0 ~ PI * 2

	//barrelEnd.x = pos.x;
	//barrelEnd.y = pos.y - barrelSize;

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;

	moveDir = MoveDir::Right;

	isAlive = true;

	// 미사일 초기화
	ammo.Init();

}

void Tank::Update()
{
	if (isAlive == false)	return;

	// 위치에 따른 모양값 갱신
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	// 포신 끝 위치 갱신
	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;


	ammo.Update();

	//AutoMove();
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyUp(VK_SPACE)) {
		Fire();
	}


	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('A'))
	{
		Move(MoveDir::Left);
	}
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('D'))
	{
		Move(MoveDir::Right);
	}

	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('S'))
	{
		Move(MoveDir::Down);
	}
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('W'))
	{
		Move(MoveDir::Up);
	}

}

void Tank::Render(HDC hdc)
{
	if (isAlive == false)	return;

	// 몸통
	Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);

	// 포신
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// 미사일
	ammo.Render(hdc);
}

void Tank::Release()
{
}

void Tank::RotateBarrelAngle(float rotateAngle)
{
	barrelAngle += (rotateAngle * PI / 180.0f);

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;
}

void Tank::Fire()
{
	ammo.SetIsAlive(true);
	ammo.SetPos(barrelEnd);	// 미사일 위치 변경
	ammo.SetIsFire(true);	// 미사일 상태 변경
	ammo.SetMoveAngle(barrelAngle); // 미사일 각도 변경
	
}

void Tank::Reload()
{
}

void Tank::AutoMove()
{
	if (shape.right >= WIN_SIZE_X)
	{
		moveDir = MoveDir::Left;
	}
	else if (shape.left <= 0)
	{
		moveDir = MoveDir::Right;
	}

	switch (moveDir)
	{
	case MoveDir::Left:		pos.x -= moveSpeed; break;
	case MoveDir::Right:	pos.x += moveSpeed; break;
	}
}

void Tank::Move(MoveDir dir)
{
	switch (dir) {
	case MoveDir::Left: pos.x -= moveSpeed; break;
	case MoveDir::Right: pos.x += moveSpeed; break;
	case MoveDir::Up: pos.y -= moveSpeed; break;
	case MoveDir::Down: pos.y += moveSpeed; break;
	}
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
