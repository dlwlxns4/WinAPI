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

		// 1. 총 3개의 스테이지를 구현.
		// 2. 각 스테이지 별로 적이 3 / 6 / 9 마리 출현한다.
		// 2-1. 적은 y 좌표 0 이상에서 x 좌표 -200 ~ winsize_x + 200 사이에서
		// 랜덤하게 출현한다.
		// 3. 3마리 당 1마리는 HP 가 3이다.
		// 4. HP별로 크기가 바뀐다.
		// 5. 적은 플레이어를 향해 직선으로 접근한다.
		// 숙제1. 유도탄을 만들어보자.

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
	// 어떻게 미사일과 적 탱크가 충돌했는지 판단할까?

	if (!target)	return false;

	// 두 원의 좌표로 거리 계산
	POINTFLOAT ammoPos = pos;
	POINTFLOAT targetPos = target->GetPos();

	float distance = sqrtf((ammoPos.x - targetPos.x) * (ammoPos.x - targetPos.x)
		+ (ammoPos.y - targetPos.y) * (ammoPos.y - targetPos.y));

	// 반지름의 합 계산
	float ammoRadius = bodySize / 2.0f;
	float targetRadius = target->GetBodySize() / 2.0f;

	float sum = ammoRadius + targetRadius;

	// 비교 (반지름의 합이 더 크면 충돌)
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
