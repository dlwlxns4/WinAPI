#include "Ammo.h"
#include "Tank.h"
#include "CommonFunction.h"

void Ammo::Init()
{
	//float x = 10.0f, y = 20.0f, h = 0.0f;
	//h = (float)sqrtf((x * x) + (y * y));


	pos.x = 0.0f;
	pos.y = 0.0f;

	bodySize = 50;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	moveSpeed = 35.0f;
	moveAngle = 0.0f;

	isFire = false;
	isAlive = true;
}

void Ammo::Update()
{
	if (isAlive == false)	return;

	if (isFire)
	{
		//pos.x += 0;
		//pos.y -= moveSpeed;

		// 1. �� 3���� ���������� ����.
		// 2. �� �������� ���� ���� 3 / 6 / 9 ���� �����Ѵ�.
		// 2-1. ���� y ��ǥ 0 �̻󿡼� x ��ǥ -200 ~ winsize_x + 200 ���̿���
		// �����ϰ� �����Ѵ�.
		// 3. 3���� �� 1������ HP �� 3�̴�.
		// 4. HP���� ũ�Ⱑ �ٲ��.
		// 5. ���� �÷��̾ ���� �������� �����Ѵ�.
		// ����1. ����ź�� ������.

		float targetAngle = atan2f(-(target->GetPos().y - pos.y), 
			(target->GetPos().x - pos.x));

		cout << "1. TargetAngle : " << targetAngle << endl;
		cout << "1. MoveAngle : " << moveAngle << endl << endl;

		float tempAngle;
		if ((targetAngle - moveAngle) > PI ||
			(targetAngle - moveAngle) < -PI)
		{
			tempAngle = (PI - (targetAngle - moveAngle)) / 9.0f;
		}
		else
		{
			tempAngle = (targetAngle - moveAngle) / 9.0f;
		}

		moveAngle += tempAngle;
		if (moveAngle > PI)	moveAngle -= PI2;
		if (moveAngle < -PI)	moveAngle += PI2;

		cout << "2. TargetAngle : " << targetAngle << endl;
		cout << "2. MoveAngle : " << moveAngle << endl << endl;


		//RotateToTarget(target->GetPos());

		pos.x += cos(moveAngle) * moveSpeed;
		pos.y -= sin(moveAngle) * moveSpeed;

		shape.left = pos.x - (bodySize / 2.0f);
		shape.top = pos.y - (bodySize / 2.0f);
		shape.right = pos.x + (bodySize / 2.0f);
		shape.bottom = pos.y + (bodySize / 2.0f);

		if (CheckCollision())
		{
			isAlive = false;
			target->SetIsAlive(false);
		}
	}
}

void Ammo::RotateToTarget(POINTFLOAT targetPos)
{
	if (!isFire) return;

	float toTargetAngle = moveAngle -
		atan2(-(targetPos.y - pos.y), targetPos.x - pos.x);

	if (toTargetAngle > PI)
	{
		toTargetAngle = -(PI * 2 - toTargetAngle);
	}
	else if (toTargetAngle < -PI)
	{
		toTargetAngle = PI * 2 + toTargetAngle;
	}

	if (toTargetAngle > 0)
	{
		moveAngle -= DEGREE_TO_RADIAN(5.0f);
	}
	else
	{
		moveAngle += DEGREE_TO_RADIAN(5.0f);
	}
}

void Ammo::SetIsFire(bool fire)
{
	this->isFire = fire;
}

void Ammo::Render(HDC hdc)
{
	if (isAlive == false)	return;

	if (isFire)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Ammo::Release()
{
}

bool Ammo::CheckCollision()
{
	// ��� �̻��ϰ� �� ��ũ�� �浹�ߴ��� �Ǵ��ұ�?

	if (!target)	return false;

	// �� ���� ��ǥ�� �Ÿ� ���
	POINTFLOAT ammoPos = pos;
	POINTFLOAT targetPos = target->GetPos();

	float distance = sqrtf((ammoPos.x - targetPos.x) * (ammoPos.x - targetPos.x)
		+ (ammoPos.y - targetPos.y) * (ammoPos.y - targetPos.y));

	// �������� �� ���
	float ammoRadius = bodySize / 2.0f;
	float targetRadius = target->GetBodySize() / 2.0f;

	float sum = ammoRadius + targetRadius;

	// �� (�������� ���� �� ũ�� �浹)
	if (distance < sum)
		return true;

	return false;
}

Ammo::Ammo()
{
}

Ammo::~Ammo()
{
}
