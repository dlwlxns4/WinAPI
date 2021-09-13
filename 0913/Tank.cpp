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
	barrelAngle = 90.0f * (PI / 180.0f);	// ������ ���� :	�� (degree) : 0 ~ 360
											//	(radian) : 0 ~ PI * 2

	//barrelEnd.x = pos.x;
	//barrelEnd.y = pos.y - barrelSize;

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;

	moveDir = MoveDir::Right;

	isAlive = true;

	// �̻��� �ʱ�ȭ
	ammo.Init();

}

void Tank::Update()
{
	if (isAlive == false)	return;

	// ��ġ�� ���� ��簪 ����
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	// ���� �� ��ġ ����
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

	// ����
	Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);

	// ����
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// �̻���
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
	ammo.SetPos(barrelEnd);	// �̻��� ��ġ ����
	ammo.SetIsFire(true);	// �̻��� ���� ����
	ammo.SetMoveAngle(barrelAngle); // �̻��� ���� ����
	
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
