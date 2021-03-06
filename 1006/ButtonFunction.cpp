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
        GENERIC_WRITE,                  //읽기, 쓰기 타입
        0, NULL,                        //공유, 보안 모드
        CREATE_ALWAYS,                  //파일을 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,          //파일 속성(읽기 전용, 숨김 등등)
        NULL);                          //

    //쓰기
    DWORD writtenByte;
    if (WriteFile(hFile,                                    //파일 핸들
        arg->tileInfo,                                       // 메모리 시작 주소
        sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,  // 메모리 크기
        &writtenByte,                                   // 실제 쓰여진 파일 용량
        NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 저장에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}

void ButtonFunction::Load(ArgumentFuncPtr* arg)
{
    string filePath = "Save/saveMapData" + to_string(arg->loadIndex) + ".map";

    HANDLE hFile = CreateFile(filePath.c_str(),
        GENERIC_READ,                  //읽기, 쓰기 타입
        0, NULL,                        //공유, 보안 모드
        OPEN_EXISTING,                  //파일을 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,          //파일 속성(읽기 전용, 숨김 등등)
        NULL);                          //

    //읽기

    DWORD readByte;
    if (ReadFile(hFile, arg->tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}

