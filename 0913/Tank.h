#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "SingleTon.h"
#include "KeyManager.h"




class Tank : public GameObject	// ��Ӱ���
{
public:
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
	Ammo ammo;

	// ���� 4��
	//Wheel wheels[4];		// ���԰���

	// �ڵ� �̵�
	MoveDir moveDir;

	bool isAlive;




public:
	void Init();		// �θ�Ŭ������ �Լ� �� ����� �ٸ� ����
	void Update();		// �������̵��� �Ѵ�
	void Render(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void AutoMove();

	//�ǽ�3. ��ũ�� �����¿�(WASD)�� ����������.
	void Move(MoveDir dir);


	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	Tank();
	~Tank();
};

