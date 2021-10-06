#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"
#include "ButtonFunction.h"

HRESULT TilemapToolScene::Init()
{

    ImageManager::GetSingleton()->AddImage("Image/button.bmp", 122, 62, 1, 2);


    arg = new ArgumentFuncPtr();
    arg->saveIndex = 0;
    arg->loadIndex = 0;
    arg->tileInfo = tileInfo;

    btnFunction = new ButtonFunction();

    saveBtn = new Button();
    saveBtn->Init(1000, 700);
    saveBtn->SetFunc(&ButtonFunction::Save, btnFunction, arg);

    loadBtn = new Button;
    loadBtn->Init(1300, 700);
    loadBtn->SetFunc(&ButtonFunction::Load, btnFunction, arg);

    SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

    sampleImage = ImageManager::GetSingleton()->AddImage("Image/maptiles.bmp",
        640, 288, 20, 9, true, RGB(255, 0, 255));
    if (sampleImage == nullptr)
    {
        cout << "Image/maptiles.bmp 로드 실패!!" << endl;
        return E_FAIL;
    }

    // 왼쪽 상단 메인 영역 초기화
    for (int i = 0; i < TILE_COUNT_Y; i++)    // y축
    {
        for (int j = 0; j < TILE_COUNT_X; j++)    // x축
        {
            SetRect(&(tileInfo[i * TILE_COUNT_X + j].rc),
                j * TILE_SIZE, i * TILE_SIZE,
                j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE);

            tileInfo[i * TILE_COUNT_X + j].frameX = 3;
            tileInfo[i * TILE_COUNT_X + j].frameY = 0;

            tileInfo[i * TILE_COUNT_X + j].terrain = Terrain::Grass;
        }
    }

    // 오른쪽 상단 샘플 영역 초기화
    for (int i = 0; i < SAMPLE_TILE_COUNT_Y; i++)    // y축
    {
        for (int j = 0; j < SAMPLE_TILE_COUNT_X; j++)    // x축
        {
            SetRect(&(sampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].rc),
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE,
                i * TILE_SIZE,
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE + TILE_SIZE,
                i * TILE_SIZE + TILE_SIZE);

            sampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].frameY = i;
        }
    }

    // 선택된 타일
    selectedSampleTile.frameX = 0;
    selectedSampleTile.frameY = 0;

    return S_OK;
}

void TilemapToolScene::Update()
{
    // 샘플영역에서 샘플을 선택
    RECT sampleArea;
    sampleArea.left = TILEMAPTOOL_SIZE_X - sampleImage->GetWidth();
    sampleArea.right = TILEMAPTOOL_SIZE_X;
    sampleArea.top = 0;
    sampleArea.bottom = sampleImage->GetHeight();

    if (PtInRect(&(sampleArea), g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - sampleArea.left;
            selectedIdX = posX / TILE_SIZE;

            int posY = g_ptMouse.y - sampleArea.top;
            selectedIdY = posY / TILE_SIZE;

            cout << selectedIdX << "  " << selectedIdY << endl;
        }
    }
    if (PtInRect(&(sampleArea), g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - sampleArea.left;
            selectedIdX = posX / TILE_SIZE;

            int posY = g_ptMouse.y - sampleArea.top;
            selectedIdY = posY / TILE_SIZE;

            selectedSampleTile.frameX =
                sampleTileInfo[selectedIdY * SAMPLE_TILE_COUNT_X + selectedIdX].frameX;
            selectedSampleTile.frameY =
                sampleTileInfo[selectedIdY * SAMPLE_TILE_COUNT_X + selectedIdX].frameY;

            cout << selectedIdX << "  " << selectedIdY << endl;
        }
    }


    // 메인영역에서 선택된 샘플 정보로 수정
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (PtInRect(&(tileInfo[i].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
            {
                tileInfo[i].frameX = selectedSampleTile.frameX;
                tileInfo[i].frameY = selectedSampleTile.frameY;
                break;
            }
        }
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
    {
        Save();
    }
    if (KeyManager::GetSingleton()->IsOnceKeyUp('L'))
    {
        Load();
    }

    saveBtn->Update();
    loadBtn->Update();
}

void TilemapToolScene::Render(HDC hdc)
{

    // 메인 영역
    for (int i = 0; i < TILE_COUNT_Y; i++)
    {
        for (int j = 0; j < TILE_COUNT_X; j++)
        {
            sampleImage->Render(hdc,
                tileInfo[i * TILE_COUNT_X + j].rc.left + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].rc.top + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].frameX,
                tileInfo[i * TILE_COUNT_X + j].frameY);

            //Rectangle(hdc, tileInfo[i * TILE_COUNT_X + j].rc.left,
            //    tileInfo[i * TILE_COUNT_X + j].rc.top,
            //    tileInfo[i * TILE_COUNT_X + j].rc.right,
            //    tileInfo[i * TILE_COUNT_X + j].rc.bottom);
        }
    }

    // 샘플 영역
    sampleImage->Render(hdc, 
        TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2,
        sampleImage->GetHeight() / 2);

    //for (int i = 0; i < SAMPLE_TILE_COUNT_X * SAMPLE_TILE_COUNT_Y; i++)
    //{
    //    Rectangle(hdc, sampleTileInfo[i].rc.left,
    //        sampleTileInfo[i].rc.top,
    //        sampleTileInfo[i].rc.right,
    //        sampleTileInfo[i].rc.bottom);
    //}

    // 선택된 타일
    sampleImage->Render(hdc, TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetFrameWidth() / 2,
        sampleImage->GetHeight() + sampleImage->GetFrameHeight() / 2 + 180,
        selectedSampleTile.frameX, selectedSampleTile.frameY, 2.5f);
    
    
    saveBtn->Render(hdc);
    loadBtn->Render(hdc);
}

void TilemapToolScene::Release()
{
    SAFE_RELEASE(loadBtn);
    SAFE_RELEASE(saveBtn);
}

void TilemapToolScene::Save(int saveIndex)
{
    string filePath = "Save/saveMapData" + to_string(saveIndex) + ".map";


    HANDLE hFile = CreateFile(filePath.c_str(),
        GENERIC_WRITE,                  //읽기, 쓰기 타입
        0, NULL,                        //공유, 보안 모드
        CREATE_ALWAYS,                  //파일을 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,          //파일 속성(읽기 전용, 숨김 등등)
        NULL);                          //

    //쓰기
    DWORD writtenByte;
    if (WriteFile(hFile,                                    //파일 핸들
        tileInfo,                                       // 메모리 시작 주소
        sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,  // 메모리 크기
        &writtenByte,                                   // 실제 쓰여진 파일 용량
        NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 저장에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}

void TilemapToolScene::Load(int loadIndex)
{
    string filePath = "Save/saveMapData" + to_string(loadIndex) + ".map";

    HANDLE hFile = CreateFile(filePath.c_str(),
        GENERIC_READ,                  //읽기, 쓰기 타입
        0, NULL,                        //공유, 보안 모드
        OPEN_EXISTING,                  //파일을 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,          //파일 속성(읽기 전용, 숨김 등등)
        NULL);                          //

    //읽기

    DWORD readByte;
    if ( ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &readByte, NULL) == false )
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}
