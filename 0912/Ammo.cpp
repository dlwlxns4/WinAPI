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

	moveSpeed = 30.0f;
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

		// 아이디어1. 발사 당시의 힘을 점점 줄여나간다. 타겟을 향하는 코드가 필요.
		// 아이디어2. 처음 발사 각도 유지 -> 각도가 타겟으로 향하도록 (발사하고 각도가 갱신)
		// 아이디어3. 업데이트함수에서 적 탱크의 좌표를 매개변수로 받아서 포탄의 포지션을 갱신
		// 아이디어4. 총알이 에너미X 좌표를 따라가면 될것 같습니다
		// 실습1. 유도탄을 만들어보자.   

		//float dist = GetDistance(pos, target->GetPos());
		//float targetAngle = atan2f(-(target->GetPos().y - pos.y), 
		//	(target->GetPos().x - pos.x));


		//float tempAngle = (targetAngle - moveAngle) / 10.0f;
		//moveAngle -= tempAngle;

		/*if (dist < 340.0f) {
			moveAngle = targetAngle;
		}*/


		//if (moveAngle > targetAngle)
		//	moveAngle -= DEGREE_TO_RADIAN(3.0f);
		//else
		//	moveAngle += DEGREE_TO_RADIAN(3.0f);

		//POINTFLOAT targetPos = target->GetPos();
		




		pos.x += cos(moveAngle) * moveSpeed;
		pos.y -= sin(moveAngle) * moveSpeed;

		shape.left = pos.x - (bodySize / 2.0f);
		shape.top = pos.y - (bodySize / 2.0f);
		shape.right = pos.x + (bodySize / 2.0f);
		shape.bottom = pos.y + (bodySize / 2.0f);

	}
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

void Ammo::CheckCollision(vector<Tank> &tank)
{
	// 어떻게 미사일과 적 탱크가 충돌했는지 판단할까?


	if (isFire) {
		for (int i = 0; i < tank.size(); i++) {
			// 두 원의 좌표로 거리 계산
			POINTFLOAT ammoPos = pos;
			POINTFLOAT targetPos = tank[i].GetPos();

			float distance = sqrtf((ammoPos.x - targetPos.x) * (ammoPos.x - targetPos.x)
				+ (ammoPos.y - targetPos.y) * (ammoPos.y - targetPos.y));

			// 반지름의 합 계산
			float ammoRadius = bodySize / 2.0f;
			float targetRadius = tank[i].GetBodySize() / 2.0f;

			float sum = ammoRadius + targetRadius;

			// 비교 (반지름의 합이 더 크면 충돌)
			if (distance < sum) {
				pos.x = 0.0f;
				pos.y = 0.0f;

				bodySize = 50;

				shape.left = 0;
				shape.top = 0;
				shape.right = 0;
				shape.bottom = 0;
 				(tank[i].HP)--;
				//0일시 삭제
				if (tank[i].HP == 0) {
					tank.erase(tank.begin() + i);
				}
			}
		}
	}
}

Ammo::Ammo()
{
}

Ammo::~Ammo()
{
}
