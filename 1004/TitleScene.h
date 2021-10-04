#pragma once
#include "GameEntity.h"
#include "Config.h"

class Image;
class TitleScene : public GameEntity
{
private:
	Image* backGround;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

