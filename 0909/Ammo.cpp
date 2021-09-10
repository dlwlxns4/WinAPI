#include "Ammo.h"

void Ammo::Init()
{
	pos.x = 0.0f;
	pos.y = 0.0f;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	moveSpeed = 10.0f;
	moveAngle = 0.0f;

	isFire = false;
	isAlive = true;
}

void Ammo::Update()
{
	if (isFire)
	{
		//pos.x += 0;
		//pos.y -= moveSpeed;

		pos.x += cos(moveAngle) * moveSpeed;
		pos.y -= sin(moveAngle) * moveSpeed;
		

		

		shape.left = pos.x - 25; shape.top = pos.y - 25;
		shape.right = pos.x + 25; shape.bottom = pos.y + 25;
	}
}

void Ammo::Render(HDC hdc)
{
	if (isFire)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Ammo::Release()
{
}

void Ammo::ChaserMisile(POINTFLOAT pos)
{
	float angle;
	if (this->isFire) {
		angle = acos( (pos.x - this->pos.x) / sqrt(pow((pos.x - this->pos.x), 2) + pow((pos.y - this->pos.y), 2)));
		if ( (int)angle >= this->moveAngle) {
			(this->moveAngle) += 0.1;
		}
		else if((int)angle <= this->moveAngle)
			(this->moveAngle) -= 0.1;
	}

}

Ammo::Ammo()
{
}

Ammo::~Ammo()
{
}
