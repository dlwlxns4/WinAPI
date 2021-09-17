#include "Tank.h"
#include "Singleton.h"
#include "KeyManager.h"

void Tank::Init(TankType type)
{
	this->type = type;

	switch (type)
	{
	case TankType::Player:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = WIN_SIZE_Y;

		bodySize = 80;
		moveSpeed = 10.0f;

		barrelSize = 140.0f;
		barrelAngle = 90.0f * (PI / 180.0f);
		break;
	case TankType::Enemy:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = 100.0f;

		bodySize = 100;
		moveSpeed = 5.0f;

		barrelSize = 140.0f;
		barrelAngle = 270.0f * (PI / 180.0f);
		break;
	}
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;

	moveDir = MoveDir::Right;

	isAlive = true;

	ammoCount = 2;
	ammoPack = new Ammo[ammoCount];
	// �̻��� �ʱ�ȭ
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Init();
	}
}

void Tank::Init(TankType type, vector<vector<Iori>> *target)
{
	this->type = type;

	switch (type)
	{
	case TankType::Player:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = WIN_SIZE_Y;

		bodySize = 80;
		moveSpeed = 10.0f;

		barrelSize = 140.0f;
		barrelAngle = 90.0f * (PI / 180.0f);
		break;
	case TankType::Enemy:
		pos.x = WIN_SIZE_X / 2.0f;
		pos.y = 100.0f;

		bodySize = 100;
		moveSpeed = 5.0f;

		barrelSize = 140.0f;
		barrelAngle = 270.0f * (PI / 180.0f);
		break;
	}
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;

	moveDir = MoveDir::Right;

	isAlive = true;

	ammoCount = 2;
	ammoPack = new Ammo[ammoCount];
	// �̻��� �ʱ�ȭ
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Init();
		ammoPack[i].SetIoriTarget(target);
	}

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

	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Update();
	}

	switch (type)
	{
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
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Render(hdc);
	}
}

void Tank::Release()
{
	delete[] ammoPack;
}

void Tank::RotateBarrelAngle(float rotateAngle)
{
	barrelAngle += (rotateAngle * PI / 180.0f);

	barrelEnd.x = pos.x + cos(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - sin(barrelAngle) * barrelSize;
}

void Tank::Fire()
{
	// �ǽ�1. �̻����� ȭ�� ���� ����� �ٽ� �߻� ������ ���·� �����Ѵ�.

	for (int i = 0; i < ammoCount; i++)
	{

		// ��ü �̻����� ��ȸ�ϸ鼭 �߻� �ƴ��� �ȵƴ��� �Ǵ�
		if (ammoPack[i].GetIsFire() && ammoPack[i].GetIsAlive())
			continue;

		ammoPack[i].SetIsAlive(true);
		ammoPack[i].SetPos(barrelEnd);	// �̻��� ��ġ ����
		ammoPack[i].SetIsFire(true);	// �̻��� ���� ����
		ammoPack[i].SetMoveAngle(barrelAngle); // �̻��� ���� ����

		break;
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

void Tank::ProcessInputKey()
{
	// Ű�Է��� Ȯ��
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
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

	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('W'))
	{
		Move(MoveDir::Up);
	}
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown('S'))
	{
		Move(MoveDir::Down);
	}
}

void Tank::Move(MoveDir dir)
{
	switch (dir)
	{
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
