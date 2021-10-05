#include "BattleScene.h"
#include "Tank.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Image.h"

HRESULT BattleScene::Init()
{

	rocket = new Tank;
	rocket->Init(TankType::Player);

	enemyManager = new EnemyManager;
	enemyManager->Init();

	Sleep(500);

	// ��� �̹���
	backGround = new Image;

	ImageManager::GetSingleton()->AddImage("Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);


	backGround = ImageManager::GetSingleton()->FindImage("Image/background.bmp");
	if (backGround == nullptr)
	{
		cout << "Image/bin.bmp ���� �ε忡 �����ߴ�." << endl;
		return E_FAIL;
	}



	return S_OK;
}

void BattleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		SceneManager::GetSingleton()->ChangeScene("Ÿ��Ʋ��");
		return;
	}

	if (rocket)
		rocket->Update();
	
	if (enemyManager)
		enemyManager->Update();
}

void BattleScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);

	if (rocket)
		rocket->Render(hdc);

	if (enemyManager)
		enemyManager->Render(hdc);
}

void BattleScene::Release()
{
	SAFE_RELEASE(enemyManager);
}
