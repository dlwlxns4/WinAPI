#include "Tank.h"

void Tank::Init()
{
	pos.x = 1200 / 2.0f;
	pos.y = 850.0f;

	bodySize = 150;
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

	// �̻��� �ʱ�ȭ
	ammo.Init();

}

void Tank::Update()
{
	ammo.Update();
}

void Tank::Render(HDC hdc)
{
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

Tank::Tank()
{
}

Tank::~Tank()
{
}
