#include "Ammo.h"
#include "Tank.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Iori.h"

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

	moveSpeed = 15.0f;
	moveAngle = 0.0f;

	target = nullptr;

	isFire = false;
	isAlive = true;


	img = new Image;
	img->Init("Image/구슬.bmp", bodySize, bodySize, true, RGB(255,0,255));
}

void Ammo::Update()
{
	if (isAlive == false)	return;

	if (isFire)
	{
		// 타겟이 있을 때만 유도 공식이 적용된다.
		if (target)
		{
			float targetAngle = atan2f(-(target->GetPos().y - pos.y),
				(target->GetPos().x - pos.x));

			cout << "1. TargetAngle : " << targetAngle << endl;
			cout << "1. MoveAngle : " << moveAngle << endl << endl;

			float tempAngle;
			float ratio = 9.0f;
			if (GetDistance(target->GetPos(), pos) < 230.0f)
			{
				ratio = 3.0f;
			}
			if ((targetAngle - moveAngle) > PI)
			{
				tempAngle = ((targetAngle - PI2) - moveAngle) / ratio;
				cout << "2_1. tempAngle : " << tempAngle << endl;
			}
			else if ((targetAngle - moveAngle) < -PI)
			{
				tempAngle = ((targetAngle + PI2) - moveAngle) / ratio;
				cout << "2_2. tempAngle : " << tempAngle << endl;
			}
			else
			{
				tempAngle = (targetAngle - moveAngle) / ratio;
				cout << "2_0. tempAngle : " << tempAngle << endl;
			}

			moveAngle += tempAngle;
			if (moveAngle > PI2)
			{
				moveAngle -= PI2;
			}
			else if (moveAngle < -PI2)
			{
				moveAngle += PI2;
			}

			cout << "2. TargetAngle : " << targetAngle << endl;
			cout << "2. MoveAngle : " << moveAngle << endl << endl;


			//RotateToTarget(target->GetPos());
		}

		pos.x += cos(moveAngle) * moveSpeed;
		pos.y -= sin(moveAngle) * moveSpeed;

		shape.left = pos.x - (bodySize / 2.0f);
		shape.top = pos.y - (bodySize / 2.0f);
		shape.right = pos.x + (bodySize / 2.0f);
		shape.bottom = pos.y + (bodySize / 2.0f);

		// 타겟과의 충돌확인
		if (CheckCollision())
		{
			isAlive = false;
			target->SetIsAlive(false);
		}

		IsCollision();

		// 화면을 벗어났는지 확인
		if (shape.left > WIN_SIZE_X || shape.right < 0 ||
			shape.top > WIN_SIZE_Y || shape.bottom < 0)
		{
			isFire = false;
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
		img->Render(hdc, pos.x, pos.y);
	}
}

void Ammo::Release()
{
	if (img)
		delete img;
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

void Ammo::IsCollision()
{
	for (int i = 0; i < targetIori[0].size(); i++) {
		for (int j = 0; j < targetIori[0][i].size(); j++) {
			if (targetIori[0][i][j].rect.left < this->pos.x && targetIori[0][i][j].rect.right  > this->pos.x && this->pos.y < targetIori[0][i][j].rect.bottom && this->pos.y > targetIori[0][i][j].rect.top) {
				this->pos.x = 0, this->pos.y = 0;
				if (targetIori[0][i].size() == 1 ) {
					targetIori[0][i].erase(targetIori[0][i].begin() + j);
					targetIori[0].erase(targetIori[0].begin() + i);
					break;
				}
				else {
					targetIori[0][i].erase(targetIori[0][i].begin() + j);
					break;
				}
			}
		}
	}
}

void Ammo::DestoryObject(int i, int j)
{
}

Ammo::Ammo()
{
}

Ammo::~Ammo()
{
	Release();
}
