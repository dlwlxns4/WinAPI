#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "SingleTon.h"
#include "KeyManager.h"
#include <vector>

using namespace std;

class Tank : public GameObject	// 상속관계
{
public:
	
	TankType type;
	
	// GameObject 상속 변수
	// 위치, 모양, 이동속도

	// 자체 멤버 변수
	// 포신 (두 점의 좌표)
	POINTFLOAT barrelEnd;
	float barrelSize;
	float barrelAngle;

	// 실습1. 스페이스 바 눌렀을 때 포신 끝에 미사일 생성
	// 실습2. 생성된 미사일이 포신 방향으로 발사(이동)
	// 2-1. 발사 이후 포신 각도가 변경되어도 최초 발사 방향으로 날아가야 함
	vector<Ammo> ammoVec;

	// 바퀴 4개
	//Wheel wheels[4];		// 포함관계

	// 자동 이동
	MoveDir moveDir;

	bool isAlive;

	Tank* target;


public:
	void Init(TankType type);		// 부모클래스의 함수 중 기능이 다른 경우는
	void Update();		// 오버라이딩을 한다
	void Render(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void AutoMove();

	//실습3. 탱크를 상하좌우(WASD)로 움직여보자.
	void Move(MoveDir dir);
	void ProcessInputKey();

	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }
	inline void SetTarget(Tank *target) { this->target = target; }

	Tank();
	~Tank();
};

