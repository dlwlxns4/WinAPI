#pragma once
#include "Config.h"
#include "GameObject.h"

class Tank;		// ���漱�� (Tank��� Ŭ������ �ִ�)
class Ammo : public GameObject
{
private:
	//Tank* owner;					// 3. Ammo��ü�� �����ڸ� �����ͷ� 
									// ������� �Ҵ�

	//POINTFLOAT enemyPos;			// 1. �� ��ǥ�� ���� ��������� ������ �ִ´�.
	Tank* target;					// 2. �� ��ü�� �޸��ּҸ� ��������� ������ �ִ´�.

	bool isFire;
	bool isAlive;

	float moveAngle;

public:
	void Init();		
	//void Init(Tank* tank);		// 1. Tank��ü�� �����͸� ����
	bool Update();
	void Render(HDC hdc);
	void Release();

	bool CheckCollision();

	void RotateToTarget(POINTFLOAT targetPos);

	// 2. Setter�� ����
	// this : this�� ȣ��� �Լ��� ȣ���� �ν��Ͻ�(�� �޸��ּ�)
	void SetIsFire(bool fire);
	inline void SetMoveAngle(float angle) { this->moveAngle = angle; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	bool isOutMap();

	Ammo();
	~Ammo();
};

