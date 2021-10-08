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
	float G;		// 출발 노드에서 현재 노드까지 이동 비용
	float H;		// 현재 노드에서 목적지까지 예상 비용

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

