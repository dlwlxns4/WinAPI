#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class Tank;
class Tank : public GameObject	// 상속관계
{
public:
	// GameObject 상속 변수
	// 위치, 모양, 이동속도

	// 자체 멤버 변수
	// 포신 (두 점의 좌표)
	Tank *target;

	POINTFLOAT barrelEnd;
	float barrelSize;
	float barrelAngle;

	// 실습1. 스페이스 바 눌렀을 때 포신 끝에 미사일 생성
	// 실습2. 생성된 미사일이 포신 방향으로 발사(이동)
	// 2-1. 발사 이후 포신 각도가 변경되어도 최초 발사 방향으로 날아가야 함
	Ammo ammo;

	// 바퀴 4개
	//Wheel wheels[4];		// 포함관계

	// 자동 이동
	MoveDir moveDir;

	bool isAlive;

	int HP=1;


public:
	void Init();		// 부모클래스의 함수 중 기능이 다른 경우는
	void Update();		// 오버라이딩을 한다
	void Render(HDC hdc);
	void EnemyRender(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void AutoMove();
	void SetShapePosition(POINTFLOAT pos) {
		// 위치에 따른 모양값 갱신
		this->pos = pos;

		shape.left = pos.x - (bodySize / 2);
		shape.top = pos.y - (bodySize / 2);
		shape.right = shape.left + bodySize;
		shape.bottom = shape.top + bodySize;
	}
	void ChaserPlayer(POINTFLOAT position);


	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }
	inline POINTFLOAT GetPosition() { return this->pos; }

	Tank();
	~Tank();
};

