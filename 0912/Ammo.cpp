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

		// ���̵��1. �߻� ����� ���� ���� �ٿ�������. Ÿ���� ���ϴ� �ڵ尡 �ʿ�.
		// ���̵��2. ó�� �߻� ���� ���� -> ������ Ÿ������ ���ϵ��� (�߻��ϰ� ������ ����)
		// ���̵��3. ������Ʈ�Լ����� �� ��ũ�� ��ǥ�� �Ű������� �޾Ƽ� ��ź�� �������� ����
		// ���̵��4. �Ѿ��� ���ʹ�X ��ǥ�� ���󰡸� �ɰ� �����ϴ�
		// �ǽ�1. ����ź�� ������.   

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
	// ��� �̻��ϰ� �� ��ũ�� �浹�ߴ��� �Ǵ��ұ�?


	if (isFire) {
		for (int i = 0; i < tank.size(); i++) {
			// �� ���� ��ǥ�� �Ÿ� ���
			POINTFLOAT ammoPos = pos;
			POINTFLOAT targetPos = tank[i].GetPos();

			float distance = sqrtf((ammoPos.x - targetPos.x) * (ammoPos.x - targetPos.x)
				+ (ammoPos.y - targetPos.y) * (ammoPos.y - targetPos.y));

			// �������� �� ���
			float ammoRadius = bodySize / 2.0f;
			float targetRadius = tank[i].GetBodySize() / 2.0f;

			float sum = ammoRadius + targetRadius;

			// �� (�������� ���� �� ũ�� �浹)
			if (distance < sum) {
				pos.x = 0.0f;
				pos.y = 0.0f;

				bodySize = 50;

				shape.left = 0;
				shape.top = 0;
				shape.right = 0;
				shape.bottom = 0;
 				(tank[i].HP)--;
				//0�Ͻ� ����
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
