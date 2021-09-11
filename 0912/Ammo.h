#pragma once
#include "Config.h"
#include "GameObject.h"
#include <vector>

using namespace std;

class Tank;		// 전방선언 (Tank라는 클래스가 있다)
class Ammo : public GameObject
{
private:
	//Tank* owner;					// 3. Ammo객체의 소유자를 포인터로 
									// 멤버변수 할당

	//POINTFLOAT enemyPos;			// 1. 적 좌표를 직접 멤버변수로 가지고 있는다.
	Tank* target;					// 2. 적 객체의 메모리주소를 멤버변수로 가지고 있는다.

	bool isFire;
	bool isAlive;

	float moveAngle;

public:
	void Init();		
	//void Init(Tank* tank);		// 1. Tank객체의 포인터를 전달
	void Update();
	void Render(HDC hdc);
	void Release();

	void CheckCollision(vector<Tank> &tank);

	// 2. Setter를 설정
	// this : this가 호출된 함수를 호출한 인스턴스(의 메모리주소)
	inline void SetIsFire(bool fire) { (*this).isFire = fire; }
	inline void SetMoveAngle(float angle) { this->moveAngle = angle; }
	inline void SetTarget(Tank* target) { this->target = target; }

	Ammo();
	~Ammo();
};

