#pragma once
#include "GameEntity.h"

class Image;
class GameObject : public GameEntity
{
//private:	// �ܺ� Ŭ������ �����Ű�� �ʴ´�.
protected:	// ��ӵ� Ŭ������ �����Ų��.
//public:		// ��� �ܺ� Ŭ������ �����Ų��.
	POINTFLOAT pos;
	RECT shape;
	float moveSpeed;
	int bodySize;

	Image* image;

public:
	void Move();

	// this�� nullptr�̴�. �ڵ������ �Լ��� ��ü�� ȣ�������� ��ü�� ����. ����
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }

	GameObject();
	~GameObject();
};

