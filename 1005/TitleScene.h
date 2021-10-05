#pragma once
#include "GameEntity.h"
#include "Config.h"

class ButtonFunction;
class Button;
class Image;
class TitleScene : public GameEntity
{
private:
	Image* backGround;
	Button* buttonGotoBattle;
	Button* buttonQuitProgram;

	ButtonFunction* buttonFunction;
	ArgumentFuncPtr* arg;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

