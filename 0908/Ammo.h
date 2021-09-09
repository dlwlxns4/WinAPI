#pragma once
#include "Config.h"
#include "GameObject.h"

class Ammo : public GameObject
{
private:
	//Tank* owner;					// 3. Ammo��ü�� �����ڸ� �����ͷ� 
									// ������� �Ҵ�

	bool isFire;
	bool isAlive;

	float moveAngle;

public:
	void Init();		
	//void Init(Tank* tank);		// 1. Tank��ü�� �����͸� ����
	void Update();
	void Render(HDC hdc);
	void Release();

	// 2. Setter�� ����
	// this : this�� ȣ��� �Լ��� ȣ���� �ν��Ͻ�(�� �޸��ּ�)
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }	
	inline void SetIsFire(bool fire) { (*this).isFire = fire; }
	inline void SetMoveAngle(float angle) { this->moveAngle = angle; }

	Ammo();
	~Ammo();
};

