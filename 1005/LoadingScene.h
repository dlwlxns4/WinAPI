#pragma once
#include "GameEntity.h"

class Image;
class LoadingScene : public GameEntity
{
private:
	Image* backGround;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

