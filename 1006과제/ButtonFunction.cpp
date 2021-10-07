#include "ButtonFunction.h"
#include "Config.h"

void ButtonFunction::ChangeScene(ArgumentFuncPtr* arg)
{
	SceneManager::GetSingleton()->ChangeScene(arg->sceneName, arg->loadingSceneName);
}

void ButtonFunction::QuitProgram(ArgumentFuncPtr* arg)
{
	PostQuitMessage(0);
}

void ButtonFunction::Save(ArgumentFuncPtr* arg)
{
    string filePath = "Save/saveMapData" + to_string(arg->saveIndex) + ".map";


    HANDLE hFile = CreateFile(filePath.c_str(),
        GENERIC_WRITE,                  //�б�, ���� Ÿ��
        0, NULL,                        //����, ���� ���
        CREATE_ALWAYS,                  //������ ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,          //���� �Ӽ�(�б� ����, ���� ���)
        NULL);                          //

    //����
    DWORD writtenByte;
    if (WriteFile(hFile,                                    //���� �ڵ�
        arg->tileInfo,                                       // �޸� ���� �ּ�
        sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,  // �޸� ũ��
        &writtenByte,                                   // ���� ������ ���� �뷮
        NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ ���忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}

void ButtonFunction::Load(ArgumentFuncPtr* arg)
{
    string filePath = "Save/saveMapData" + to_string(arg->loadIndex) + ".map";

    HANDLE hFile = CreateFile(filePath.c_str(),
        GENERIC_READ,                  //�б�, ���� Ÿ��
        0, NULL,                        //����, ���� ���
        OPEN_EXISTING,                  //������ ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,          //���� �Ӽ�(�б� ����, ���� ���)
        NULL);                          //

    //�б�

    DWORD readByte;
    if (ReadFile(hFile, arg->tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}

