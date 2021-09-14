#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "SingleTon.h"
#include "KeyManager.h"
#include <vector>

using namespace std;

class Tank : public GameObject	// ��Ӱ���
{
public:
	
	TankType type;
	
	// GameObject ��� ����
	// ��ġ, ���, �̵��ӵ�

	// ��ü ��� ����
	// ���� (�� ���� ��ǥ)
	POINTFLOAT barrelEnd;
	float barrelSize;
	float barrelAngle;

	// �ǽ�1. �����̽� �� ������ �� ���� ���� �̻��� ����
	// �ǽ�2. ������ �̻����� ���� �������� �߻�(�̵�)
	// 2-1. �߻� ���� ���� ������ ����Ǿ ���� �߻� �������� ���ư��� ��
	vector<Ammo> ammoVec;

	// ���� 4��
	//Wheel wheels[4];		// ���԰���

	// �ڵ� �̵�
	MoveDir moveDir;

	bool isAlive;

	Tank* target;


public:
	void Init(TankType type);		// �θ�Ŭ������ �Լ� �� ����� �ٸ� ����
	void Update();		// �������̵��� �Ѵ�
	void Render(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void AutoMove();

	//�ǽ�3. ��ũ�� �����¿�(WASD)�� ����������.
	void Move(MoveDir dir);
	void ProcessInputKey();

	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }
	inline void SetTarget(Tank *target) { this->target = target; }

	Tank();
	~Tank();
};

