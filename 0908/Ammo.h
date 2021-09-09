#pragma once
#include "Config.h"
#include "GameObject.h"

class Ammo : public GameObject
{
private:
	//Tank* owner;					// 3. Ammo객체의 소유자를 포인터로 
									// 멤버변수 할당

	bool isFire;
	bool isAlive;

	float moveAngle;

public:
	void Init();		
	//void Init(Tank* tank);		// 1. Tank객체의 포인터를 전달
	void Update();
	void Render(HDC hdc);
	void Release();

	// 2. Setter를 설정
	// this : this가 호출된 함수를 호출한 인스턴스(의 메모리주소)
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }	
	inline void SetIsFire(bool fire) { (*this).isFire = fire; }
	inline void SetMoveAngle(float angle) { this->moveAngle = angle; }

	Ammo();
	~Ammo();
};

