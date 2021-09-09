#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class Tank : public GameObject
{
public:
	// GameObject ��� ����
	// ��ġ, ���, �̵��ӵ�
	int bodySize;

	// ��ü ��� ����
	// ���� (�� ���� ��ǥ)
	POINTFLOAT barrelEnd;
	float barrelSize;
	float barrelAngle;

	// �ǽ�1. �����̽� �� ������ �� ���� ���� �̻��� ����
	// �ǽ�2. ������ �̻����� ���� �������� �߻�(�̵�)
	// 2-1. �߻� ���� ���� ������ ����Ǿ ���� �߻� �������� ���ư��� ��
	Ammo ammo;


public:
	void Init();		// �θ�Ŭ������ �Լ� �� ����� �ٸ� ����
	void Update();		// �������̵��� �Ѵ�
	void Render(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();

	Tank();
	~Tank();
};

