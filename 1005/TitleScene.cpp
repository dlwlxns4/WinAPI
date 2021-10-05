#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

HRESULT TitleScene::Init()
{
	// 타티을 씬에서 사용할 UI 이미지도 로드해놓자.
	ImageManager::GetSingleton()->AddImage("Image/button.bmp", 122, 62, 1, 2);


	ImageManager::GetSingleton()->AddImage("Image/bin.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/bin.bmp");


	buttonFunction = new ButtonFunction;

	// 매개변수 (어떤 씬으로, 어떤 로딩씬을)

	arg = new ArgumentFuncPtr;

	arg->sceneName = "전투씬";
	arg->lodingSceneName = "로딩씬";
	buttonGotoBattle = new Button;
	buttonGotoBattle->Init(100,100);
	buttonGotoBattle->SetFunc(&ButtonFunction::ChangeScene, buttonFunction, arg);

	buttonQuitProgram = new Button;
	buttonQuitProgram->Init(WIN_SIZE_X-100, 100);
	buttonQuitProgram->SetFunc(&ButtonFunction::QuitProgram, buttonFunction, arg);
	
	return S_OK;
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("전투씬", "로딩씬");
		return;
	}

	if (buttonGotoBattle)
		buttonGotoBattle->Update();
	if (buttonQuitProgram)
		buttonQuitProgram->Update();
}

void TitleScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);

	if (buttonGotoBattle)
		buttonGotoBattle->Render(hdc);
	if (buttonQuitProgram)
		buttonQuitProgram->Render(hdc);
}

void TitleScene::Release()
{
	SAFE_RELEASE(buttonGotoBattle);
	SAFE_RELEASE(buttonQuitProgram);
	SAFE_DELETE(buttonFunction);
	SAFE_DELETE(arg);
}
