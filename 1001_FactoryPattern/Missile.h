#pragma once
class Missile		// interface
{
private:
	// 멤버변수

public:
	// 멤버함수
	virtual void Move() = 0;		// 가상함수 / <순수가상함수>
	virtual void Notice() = 0;		// 미사일 생성 시 알림

	Missile() {}
	virtual ~Missile();
};

// 미사일 1) 발사된 최초 각도로 날아가는 미사일
class NormalMissile : public Missile
{
public:
	virtual void Move() override;
	virtual void Notice() override;

	NormalMissile() {}
	virtual ~NormalMissile();
};

// 미사일 2) 유도탄 타겟이 있을 때 타겟의 위치를 실시간으로 추적하는 미사일
class HommingMissile : public Missile
{
public:
	virtual void Move() override;
	virtual void Notice() override;

	HommingMissile() {}
	virtual ~HommingMissile();
};

// 미사일 3) 발사된 후 일정시간 이후에 36개로 분할하는 미사일
class FireworkMissile : public Missile
{
	/*Missile* m;*/
public:
	virtual void Move() override;
	virtual void Notice() override;

	FireworkMissile() {}
	virtual ~FireworkMissile();	// __vfptr 에 (가상함수테이블) 추가된다.
};

