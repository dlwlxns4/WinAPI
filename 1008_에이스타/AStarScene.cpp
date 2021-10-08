#include "AStarScene.h"
#include "CommonFunction.h"

HRESULT AstarTile::Init()
{
    return E_NOTIMPL;
}

HRESULT AstarTile::Init(int idX, int idY)
{
    this->idX = idX;
    this->idY = idY;

    center.x = idX;// *ASTAR_TILE_SIZE + ASTAR_TILE_SIZE / 2;
    center.y = idY;// *ASTAR_TILE_SIZE + ASTAR_TILE_SIZE / 2;

    rc.left = idX * ASTAR_TILE_SIZE;
    rc.top = idY * ASTAR_TILE_SIZE;
    rc.right = rc.left + ASTAR_TILE_SIZE;
    rc.bottom = rc.top + ASTAR_TILE_SIZE;

    F = 0.0f; G = 0.0f; H = 0.0f;

    type = AstarTileType::None;

    color = RGB(205,255,205);
    hBrush = CreateSolidBrush(color);
    
    hTypeBrush[AstarTileType::Start] = CreateSolidBrush(RGB(206, 9, 53));
    hTypeBrush[AstarTileType::Dest] = CreateSolidBrush(RGB(61, 209, 94));
    hTypeBrush[AstarTileType::Wall] = CreateSolidBrush(RGB(94, 94, 94));
    hTypeBrush[AstarTileType::Walkable] = CreateSolidBrush(RGB(194, 194, 194));
    hTypeBrush[AstarTileType::Curr] = CreateSolidBrush(RGB(255, 0, 255));
    hTypeBrush[AstarTileType::Closed] = CreateSolidBrush(RGB(0, 0, 0));
    hTypeBrush[AstarTileType::Path] = CreateSolidBrush(RGB(0, 255, 0));
    hTypeBrush[AstarTileType::None] = CreateSolidBrush(RGB(205, 255, 205));

    return S_OK;
}

void AstarTile::Update()
{
}

void AstarTile::Render(HDC hdc)
{
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    FillRect(hdc, &rc, hBrush);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);


    SelectObject(hdc, hOldBrush);
}

void AstarTile::Release()
{
    for (int i = 0; i < AstarTileType::End; i++)
    {
        DeleteObject(hTypeBrush[i]);
    }

    DeleteObject(hBrush);
}

void AstarTile::SetType(AstarTileType type)
{
    this->type = type; 
   
    hBrush = hTypeBrush[type];
}

HRESULT AStarScene::Init()
{
    SetWindowSize(30, 30, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);


    for (int i = 0; i < ASTAR_TILE_COUNT; i++)
    {
        for (int j = 0; j < ASTAR_TILE_COUNT; j++)
        {
            map[i][j].Init(j, i);
        }
    }

    currTile = nullptr;
    
    return S_OK;
}

void AStarScene::Update()
{
    RECT astarArea = { 0, 0, ASTAR_TILE_COUNT * ASTAR_TILE_SIZE,  ASTAR_TILE_COUNT * ASTAR_TILE_SIZE };

    if (PtInRect(&astarArea, g_ptMouse))
    {
        int idX = g_ptMouse.x / ASTAR_TILE_SIZE;
        int idY = g_ptMouse.y / ASTAR_TILE_SIZE;

        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
            {
                map[startPoint.y][startPoint.x].SetType(AstarTileType::None);
                map[idY][idX].SetType(AstarTileType::Start);
                startPoint.x = idX;
                startPoint.y = idY;

                currTile = &(map[idY][idX]);
            }
            else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
            {
                map[destPoint.y][destPoint.x].SetType(AstarTileType::None);
                map[idY][idX].SetType(AstarTileType::Dest);
                destPoint.y = idY;
                destPoint.x = idX;
            }
            else
            {
                map[idY][idX].SetType(AstarTileType::Wall);
            }
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
        {
            map[idY][idX].SetType(AstarTileType::None);
        }
    }
    //����Ű ������ ��ã�� 1ȸ ����
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
    {
        FindPath();
    }
}

void AStarScene::Render(HDC hdc)
{
    for (int i = 0; i < ASTAR_TILE_COUNT; i++)
    {
        for (int j = 0; j < ASTAR_TILE_COUNT; j++)
        {
            map[i][j].Render(hdc);
        }
    }
}

void AStarScene::Release()
{
}

void AStarScene::FindPath()
{

   

    // 1. ���� ����� �����¿� ��� �� �ĺ� ��带 ã�´�.
    //Step1
    if (AddOpenList(currTile))
    {
        // ���¸���Ʈ�� �ִ� �ĺ��� �߿� F ���� ���� ���� ��带 ã�´�.
        //Step2
        currTile = GetMinFTile();
        currTile->SetType(AstarTileType::Curr);
    }
    else//������ ã���� �� 
    {
        // ��θ� ����Ѵ�.
        PrintPath();
    }
}

bool AStarScene::AddOpenList(AstarTile* currTile)
{
    int tmpIdX, tmpIdY;
#pragma region Step1
    for (int i = -1; i <= 1; i += 2) //����
    {
        if (currTile->GetIdY() == 0 && i == -1) continue;
        if (currTile->GetIdY() == ASTAR_TILE_COUNT - 1 && i == 1) continue;

        tmpIdY = currTile->GetIdY() + i;
        tmpIdX = currTile->GetIdX();

        if (map[tmpIdY][tmpIdX].GetType() == AstarTileType::Dest)
        {
            map[destPoint.y][destPoint.x].SetParentTile(currTile);
            return false;
        }


        // �����¿��� ����� �̵��� �� �ִ� Ÿ���̸� ���¸���Ʈ�� �߰�
        if (map[tmpIdY][tmpIdX].GetType() == AstarTileType::None)
        {
            map[tmpIdY][tmpIdX].SetType(AstarTileType::Walkable);
            map[tmpIdY][tmpIdX].SetParentTile(currTile);
            openList.push_back(&map[tmpIdY][tmpIdX]);
        }

    }

    for (int j = -1; j <= 1; j += 2) // �¿�
    {
        if (currTile->GetIdX() == 0 && j == -1) continue;
        if (currTile->GetIdX() == ASTAR_TILE_COUNT - 1 && j == 1) continue;

        tmpIdX = currTile->GetIdX() + j;
        tmpIdY = currTile->GetIdY();

        if (map[tmpIdY][tmpIdX].GetType() == AstarTileType::Dest)
        {
            map[destPoint.y][destPoint.x].SetParentTile(currTile);
            false;
        }

        // �����¿��� ��尡 �̵��� �� �ִ� Ÿ���̸� ���¸���Ʈ�� �߰�
        if (map[tmpIdY][tmpIdX].GetType() == AstarTileType::None)
        {
            map[tmpIdY][tmpIdX].SetType(AstarTileType::Walkable);
            map[tmpIdY][tmpIdX].SetParentTile(currTile);
            openList.push_back(&map[tmpIdY][tmpIdX]);
        }
    }

    currTile->SetType(AstarTileType::Closed);
#pragma endregion

    return true;
}

AstarTile* AStarScene::GetMinFTile()
{
#pragma region Step2
    float F, G, H;
    float minF = FLT_MAX;

    vector<AstarTile*>::iterator it = openList.begin();
    vector<AstarTile*>::iterator itmp;
    for (; it != openList.end(); it++)
    {
        G = (*it)->GetParentTile()->GetG() + 10;
        (*it)->SetG(G);
        //float h = /*���� ��忡�� ������ �������� ���� ���*/
        H = GetDistance((*it)->GetCenter(), map[destPoint.y][destPoint.x].GetCenter()) * 10;
        (*it)->SetH(H);
        F = G + H;
        (*it)->SetF(F);

        if (minF > F)
        {
            minF = F;
            itmp = it;
            currTile = (*it);
        }
    }

#pragma endregion
    currTile = (*itmp);
    openList.erase(itmp);


    return currTile;
}

void AStarScene::PrintPath()
{
    AstarTile* currPathTile = &map[destPoint.y][destPoint.x];

    while (currPathTile != &(map[startPoint.y][startPoint.x]))
    {
        currPathTile = currPathTile->GetParentTile();
        currPathTile->SetType(AstarTileType::Path);
    }

}
