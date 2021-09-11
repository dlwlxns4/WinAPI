#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class Tank;
class Tank : public GameObject	// ��Ӱ���
{
public:
	// GameObject ��� ����
	// ��ġ, ���, �̵��ӵ�

	// ��ü ��� ����
	// ���� (�� ���� ��ǥ)
	Tank *target;

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

	int HP=1;


public:
	void Init();		// �θ�Ŭ������ �Լ� �� ����� �ٸ� ����
	void Update();		// �������̵��� �Ѵ�
	void Render(HDC hdc);
	void EnemyRender(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void AutoMove();
	void SetShapePosition(POINTFLOAT pos) {
		// ��ġ�� ���� ��簪 ����
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

