#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

HRESULT TitleScene::Init()
{
	// ŸƼ�� ������ ����� UI �̹����� �ε��س���.
	ImageManager::GetSingleton()->AddImage("Image/button.bmp", 122, 62, 1, 2);


	ImageManager::GetSingleton()->AddImage("Image/bin.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/bin.bmp");


	buttonFunction = new ButtonFunction;

	// �Ű����� (� ������, � �ε�����)

	arg = new ArgumentFuncPtr;

	arg->sceneName = "������";
	arg->lodingSceneName = "�ε���";
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
		SceneManager::GetSingleton()->ChangeScene("������", "�ε���");
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
