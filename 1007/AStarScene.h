#pragma once
#include "Config.h"
#include "GameEntity.h"

class AstarTile : public GameEntity
{
private:
	int idX, idY;
	RECT rc;
	POINT center;

	float F;		// G+H
	float G;		// ��� ��忡�� ���� ������ �̵� ���
	float H;		// ���� ��忡�� ���������� ���� ���

	AstarTile* parentTile;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};


class AStarScene : public GameEntity
{
private:
	AstarTile map[20][20];

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

