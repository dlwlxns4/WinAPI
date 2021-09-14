#include "Tank.h"



void Tank::Init(TankType type)
{
	this->type = type;
	
	switch (type) {
	case TankType ::Player:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = WIN_SIZE_Y - 50;

		bodySize = 50;

		moveSpeed = 10.0f;

		barrelSize = 140.0f;
		barrelAngle = 90.0f * (PI / 180.0f);	// ������ ���� :	�� (degree) : 0 ~ 360
		break;
	case TankType ::Enemy:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = WIN_SIZE_Y - 100;

		bodySize = 100;


		moveSpeed = 10.0f;

		barrelSize = 140.0f;
		barrelAngle = 270.0f * (PI / 180.0f);	// ������ ���� :	�� (degree) : 0 ~ 360
		break;
	}

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	//barrelEnd.x = pos.x;
	//barrelEnd.y = pos.y - barrelSize;

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;

	moveDir = MoveDir::Right;

	isAlive = true;

	// �̻��� �ʱ�ȭ

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

	for (int i = 0; i < ammoVec.size(); i++) {
		bool isCollision = ammoVec[i].Update();
		if (isCollision) ammoVec.erase(ammoVec.begin() + i);
	}


	switch (type) {
	case TankType::Player:
		ProcessInputKey();
		break;
	case TankType::Enemy:
		AutoMove();
		break;
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
	for (int i = 0; i < ammoVec.size(); i++) {
		ammoVec[i].Render(hdc);
	}
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
	if (ammoVec.size() < 3) {
		Ammo ammo;
		ammo.Init();
		ammo.SetTarget(this->target);
		ammo.SetIsAlive(true);
		ammo.SetPos(barrelEnd);	// �̻��� ��ġ ����
		ammo.SetIsFire(true);	// �̻��� ���� ����
		ammo.SetMoveAngle(barrelAngle); // �̻��� ���� ����
		ammoVec.push_back(ammo);
	}
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

void Tank::ProcessInputKey()
{
	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('A')){
		Move(MoveDir::Left);
	}
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('D')){
		Move(MoveDir::Right);
	}

	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('S')){
		Move(MoveDir::Down);
	}
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('W')){
		Move(MoveDir::Up);
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE)) {
		Fire();
	}
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
