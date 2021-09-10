#include "Tank.h"

void Tank::Init()
{
	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = WIN_SIZE_Y - 50;

	bodySize = 150;


	moveSpeed = 0.0f;

	barrelSize = 140.0f;
	barrelAngle = 90.0f * (PI / 180.0f);	// ������ ���� :	�� (degree) : 0 ~ 360
											//	(radian) : 0 ~ PI * 2

	//barrelEnd.x = pos.x;
	//barrelEnd.y = pos.y - barrelSize;
	
	moveDir = MoveDir::Right;


	// �̻��� �ʱ�ȭ
	ammo.Init();

}

void Tank::Update()
{
	// ��ġ�� ���� ��簪 ����
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	//���� �� ��ġ ����

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;


	ammo.Update();
	
	AutoMove();
}

void Tank::Render(HDC hdc)
{
	//
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

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
	ammo.SetPos(barrelEnd);	// �̻��� ��ġ ����
	ammo.SetIsFire(true);	// �̻��� ���� ����
	ammo.SetMoveAngle(barrelAngle); // �̻��� ���� ����
}

void Tank::Reload()
{
}

void Tank::AutoMove()
{
	if (shape.right >= WIN_SIZE_X) {
		moveDir = MoveDir::Left;
	}
	else if (shape.right <= 0) {
		moveDir = MoveDir::Right;
	}

	switch (moveDir) {
	case MoveDir::Left:		pos.x -= moveSpeed;		break;
	case MoveDir::Right:	pos.x += moveSpeed;		break;
	}
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
