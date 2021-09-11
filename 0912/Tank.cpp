#include "Tank.h"
#include <vector>

using namespace std;
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


	// ���� �� ��ġ ����
	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;


	ammo.Update();


	
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

void Tank::EnemyRender(HDC hdc)
{
	if (isAlive == false)	return;

	if (HP == 1) {
		bodySize = 50;
		// ��ġ�� ���� ��簪 ����
		shape.left = pos.x - (bodySize / 2);
		shape.top = pos.y - (bodySize / 2);
		shape.right = shape.left + bodySize;
		shape.bottom = shape.top + bodySize;
	}
	else if (HP == 2) {
		bodySize = 100;
		// ��ġ�� ���� ��簪 ����
		shape.left = pos.x - (bodySize / 2);
		shape.top = pos.y - (bodySize / 2);
		shape.right = shape.left + bodySize;
		shape.bottom = shape.top + bodySize;
	}
	else if (HP == 3) {
		// ��ġ�� ���� ��簪 ����

		bodySize = 150;
		shape.left = pos.x - (bodySize / 2);
		shape.top = pos.y - (bodySize / 2);
		shape.right = shape.left + bodySize;
		shape.bottom = shape.top + bodySize;
	}

	// ����
	Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);



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




void Tank::ChaserPlayer(POINTFLOAT position)
{
	// ��ġ�� ���� ��簪 ����
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	// ���� �� ��ġ ����
	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;


	if (pos.x > position.x)
		pos.x -= moveSpeed/4;
	else if (pos.x == position.x) {

	}
	else {
		pos.x += moveSpeed/4;
	}
	
	pos.y += 5;
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
