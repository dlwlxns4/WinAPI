#include "Button.h"
#include "Image.h"
#include "ButtonFunction.h"

HRESULT Button::Init()
{
	return E_NOTIMPL;
}

HRESULT Button::Init(int posX, int posY)
{
	image = ImageManager::GetSingleton()->FindImage("Image/button.bmp");
	pos.x = posX;
	pos.y = posY;

	shape.left = pos.x - image->GetFrameWidth()/2;
	shape.top = pos.y - image->GetFrameHeight()/2;
	shape.right = pos.x + image->GetFrameWidth()/2;
	shape.bottom = pos.y + image->GetFrameHeight() / 2;

	state = Button_State::None;

	return S_OK;
}

void Button::Update()
{
	// 마우스 커서가 충돌 영역에 들어갔는지
	if(PtInRect(&shape, g_ptMouse))
	{
		if(KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = Button_State::Down;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && state==Button_State::Down)
		{
			state = Button_State::Up;
			//버튼 기능 수행
			if (bf && pFunc)
				(bf->*pFunc)(arg);

			
		}
	}
	else
	{
		state = Button_State::None;
	}
}

void Button::Render(HDC hdc)
{
	switch(state)
	{
	case Button_State::None:
	case Button_State::Up:
		if (image)
			image->Render(hdc, pos.x, pos.y, 0, 0);
		break;
	case Button_State::Down:
		if (image)
			image->Render(hdc, pos.x, pos.y, 0, 1);
		break;

	}
}

void Button::Release()
{
}
