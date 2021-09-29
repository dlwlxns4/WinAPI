#include <Windows.h>

// 전역변수
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)TEXT("윈메인의 시작");

// 타이머 객체를 생성할 수 있다.
HANDLE		g_hTimer;
int enemyAttackTimer=0;

#define MOVE_SPEED	5

enum NemoType { Big_1, Big_2, Small_1, Small_2, End };
enum MoveDir { Left, Right, Up, Down };

struct Nemo
{
	int posX, posY;
	int left, top, right, bottom;
	int size;
	MoveDir dir;
	bool isFire, isAlive;
	int HP = 3;
};

void InitNemos(Nemo* nemos)
{
	nemos[NemoType::Big_1].posX = 150;
	nemos[NemoType::Big_1].posY = 550;
	nemos[NemoType::Big_1].size = 100;
	nemos[NemoType::Big_1].left = nemos[NemoType::Big_1].posX - (nemos[NemoType::Big_1].size / 2);
	nemos[NemoType::Big_1].right = nemos[NemoType::Big_1].left + nemos[NemoType::Big_1].size;
	nemos[NemoType::Big_1].top = nemos[NemoType::Big_1].posY - (nemos[NemoType::Big_1].size / 2);
	nemos[NemoType::Big_1].bottom = nemos[NemoType::Big_1].top + nemos[NemoType::Big_1].size;
	nemos[NemoType::Big_1].dir = MoveDir::Left;
	nemos[NemoType::Big_1].isFire = false;
	nemos[NemoType::Big_1].isAlive = true;

	nemos[NemoType::Big_2].posX = 350;
	nemos[NemoType::Big_2].posY = 150;
	nemos[NemoType::Big_2].size = 100;
	nemos[NemoType::Big_2].left = nemos[NemoType::Big_2].posX - (nemos[NemoType::Big_2].size / 2);
	nemos[NemoType::Big_2].right = nemos[NemoType::Big_2].left + nemos[NemoType::Big_2].size;
	nemos[NemoType::Big_2].top = nemos[NemoType::Big_2].posY - (nemos[NemoType::Big_2].size / 2);
	nemos[NemoType::Big_2].bottom = nemos[NemoType::Big_2].top + nemos[NemoType::Big_2].size;
	nemos[NemoType::Big_2].dir = MoveDir::Left;
	nemos[NemoType::Big_2].isFire = false;
	nemos[NemoType::Big_2].isAlive = true;

	nemos[NemoType::Small_1].posX = 150;
	nemos[NemoType::Small_1].posY = 550;
	nemos[NemoType::Small_1].size = 50;
	nemos[NemoType::Small_1].left = nemos[NemoType::Small_1].posX - (nemos[NemoType::Small_1].size / 2);
	nemos[NemoType::Small_1].right = nemos[NemoType::Small_1].left + nemos[NemoType::Small_1].size;
	nemos[NemoType::Small_1].top = nemos[NemoType::Small_1].posY - (nemos[NemoType::Small_1].size / 2);
	nemos[NemoType::Small_1].bottom = nemos[NemoType::Small_1].top + nemos[NemoType::Small_1].size;
	nemos[NemoType::Small_1].dir = MoveDir::Up;
	nemos[NemoType::Small_1].isFire = false;
	nemos[NemoType::Small_1].isAlive = true;

	nemos[NemoType::Small_2].posX = 350;
	nemos[NemoType::Small_2].posY = 150;
	nemos[NemoType::Small_2].size = 50;
	nemos[NemoType::Small_2].left = nemos[NemoType::Small_2].posX - (nemos[NemoType::Small_2].size / 2);
	nemos[NemoType::Small_2].right = nemos[NemoType::Small_2].left + nemos[NemoType::Small_2].size;
	nemos[NemoType::Small_2].top = nemos[NemoType::Small_2].posY - (nemos[NemoType::Small_2].size / 2);
	nemos[NemoType::Small_2].bottom = nemos[NemoType::Small_2].top + nemos[NemoType::Small_2].size;
	nemos[NemoType::Small_2].dir = MoveDir::Down;
	nemos[NemoType::Small_2].isFire = false;
	nemos[NemoType::Small_2].isAlive = true;
}

void DrawRect(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x + size, y);
	LineTo(hdc, x, y);
}

void DrawNemos(HDC hdc, const Nemo* nemos) /*const*/	// 멤버변수의 값을 변경하지 않겠다
{
	for (int i = 0; i < NemoType::End; i++)
	{
		if (nemos[i].isAlive)
		{
			DrawRect(hdc, nemos[i].left, nemos[i].top, nemos[i].size);
		}
	}
}

void SetNemoData(Nemo* nemo)
{
	nemo->left = nemo->posX - (nemo->size / 2);
	nemo->top = nemo->posY - (nemo->size / 2);
	nemo->right = nemo->left + nemo->size;
	nemo->bottom = nemo->top + nemo->size;
}

bool IsCollision(Nemo nemo1, Nemo nemo2)
{
	// 4가지 겹치지 않을 상황을 모두 확인할 필요가 있을 때
	if (nemo1.left > nemo2.right)	return false;
	if (nemo1.right < nemo2.left)	return false;
	if (nemo1.top > nemo2.bottom)	return false;
	if (nemo1.bottom < nemo2.top)	return false;

	return true;
}


void decreaseHP(Nemo& nemo) {
	(nemo.HP)--;
}

void ProcessInputKey(WPARAM wParam, Nemo* nemos, NemoType& controlID, NemoType& notControlID)
{
	switch (wParam)
	{
	case VK_UP:
		nemos[controlID].posY -= MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].bottom < nemos[NemoType::Small_1].bottom && !nemos[NemoType::Small_1].isFire)
		{
			nemos[NemoType::Small_1].posY =
				nemos[controlID].bottom - (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	case VK_DOWN:
		nemos[controlID].posY += MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].top > nemos[NemoType::Small_1].top && !nemos[NemoType::Small_1].isFire)
		{
			nemos[NemoType::Small_1].posY =
				nemos[controlID].top + (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	case VK_LEFT:
		nemos[controlID].posX -= MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].right < nemos[NemoType::Small_1].right && !nemos[NemoType::Small_1].isFire)
		{
			nemos[NemoType::Small_1].posX =
				nemos[controlID].right - (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	case VK_RIGHT:
		nemos[controlID].posX += MOVE_SPEED;

		SetNemoData(&nemos[controlID]);

		// 작은 네모 충돌확인
		if (nemos[controlID].left > nemos[NemoType::Small_1].left && !nemos[NemoType::Small_1].isFire)
		{
			nemos[NemoType::Small_1].posX =
				nemos[controlID].left + (nemos[NemoType::Small_1].size / 2);

			SetNemoData(&nemos[NemoType::Small_1]);
		}
		break;
	}

	// 큰 네모끼리 충돌확인
	if (IsCollision(nemos[controlID], nemos[notControlID]))
	{
		// 작은 네모의 위치를 옮긴다.
		nemos[NemoType::Small_1].posX = nemos[notControlID].posX;
		nemos[NemoType::Small_1].posY = nemos[notControlID].posY;

		SetNemoData(&nemos[NemoType::Small_1]);

		// 제어권도 옮긴다.
		controlID = controlID == NemoType::Big_1 ? NemoType::Big_2 : NemoType::Big_1;
		notControlID = notControlID == NemoType::Big_1 ? NemoType::Big_2 : NemoType::Big_1;
	}

	InvalidateRect(g_hWnd, NULL, true);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우를 생성하기 위한 기본 셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 핸들형변환
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = WndProc;				// 함수포인터(콜백함수)
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;	// bit연산

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 
		400, 100, 1200, 900, NULL, NULL, _hInstance, NULL);

	// 타이머 셋팅
	g_hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	// 메시지 큐에 있는 메시지 처리
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);

	return message.wParam;
}

void EnemyAttack(Nemo *nemos) {
	//적 개체 총알 타이머
	if (nemos[NemoType::Small_2].posX == nemos[NemoType::Big_2].posX && nemos[NemoType::Small_2].posY == nemos[NemoType::Big_2].posY)
		enemyAttackTimer++;

	if (enemyAttackTimer >= 10) {
		nemos[NemoType::Small_2].isFire = true;

		nemos[NemoType::Small_2].posY += 30;

		if (nemos[NemoType::Small_2].top >= 900)
		{
			enemyAttackTimer = 0;
			nemos[NemoType::Small_2].isFire = false;
			nemos[NemoType::Small_2].posX = nemos[NemoType::Big_2].posX;
			nemos[NemoType::Small_2].posY = nemos[NemoType::Big_2].posY;
		}

		SetNemoData(&nemos[NemoType::Small_1]);
	}
}

void EnemyMove(Nemo* nemos) {
	if (nemos[NemoType::Big_2].isAlive)
	{
		switch (nemos[NemoType::Big_2].dir)
		{
		case MoveDir::Left:
			nemos[NemoType::Big_2].posX -= 10;
			if (!nemos[NemoType::Small_2].isFire)
				nemos[NemoType::Small_2].posX -= 10;
			break;
		case MoveDir::Right:
			nemos[NemoType::Big_2].posX += 10;
			if (!nemos[NemoType::Small_2].isFire)
				nemos[NemoType::Small_2].posX += 10;
			break;
		}
		SetNemoData(&nemos[NemoType::Big_2]);
		SetNemoData(&nemos[NemoType::Small_2]);

		// 벽에 부딪혔는지 확인
		if (nemos[NemoType::Big_2].left <= 0 ||
			nemos[NemoType::Big_2].right >= 1200)
		{
			//moveSpeed = moveSpeed > 0 ? -10 : 10;

			//nemos[NemoType::Big_2].posX += 10;
			//SetNemoData(&nemos[NemoType::Big_2]);
			nemos[NemoType::Big_2].dir = nemos[NemoType::Big_2].dir == MoveDir::Left ?
				MoveDir::Right : MoveDir::Left;
		}
	}

}

void FireBullet(Nemo *nemos) {
	// 작은 네모(미사일) 이동
	if (nemos[NemoType::Small_1].isAlive && nemos[NemoType::Small_1].isFire)
	{
		nemos[NemoType::Small_1].posY -= 30;

		if (nemos[NemoType::Small_1].bottom <= 0)
		{
			nemos[NemoType::Small_1].isFire = false;
			nemos[NemoType::Small_1].posX = nemos[NemoType::Big_1].posX;
			nemos[NemoType::Small_1].posY = nemos[NemoType::Big_1].posY;
		}

		SetNemoData(&nemos[NemoType::Small_1]);
	}
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	char text[128];

	static NemoType controlID = NemoType::Big_1;
	static NemoType notControlID = NemoType::Big_2;
	static Nemo nemos[NemoType::End];
	static int mousePosX = 0, mousePosY = 0;
	static int clickedMousePosX = 0, clickedMousePosY = 0;

	int moveSpeed = 10;

	switch (iMessage)
	{
	case WM_CREATE:
		InitNemos(nemos);
		break;
	case WM_TIMER:
		
		// 이동
		//nemos[NemoType::Big_2].left -= 10;

		//nemos[NemoType::Big_2].posX += moveSpeed;


		//적 움직임
		EnemyMove(nemos);
		//적 공격
		EnemyAttack(nemos);

#pragma region 내 충돌
		// 충돌확인
		if (IsCollision(nemos[NemoType::Small_2], nemos[NemoType::Big_1]))
		{
			decreaseHP(nemos[NemoType::Big_1]);

			nemos[NemoType::Small_2].isFire = false;

			nemos[NemoType::Small_2].posX = nemos[NemoType::Big_2].posX;
			nemos[NemoType::Small_2].posY = nemos[NemoType::Big_2].posY;

			SetNemoData(&nemos[NemoType::Small_2]);
			if (nemos[NemoType::Big_1].HP <= 0) {
				nemos[NemoType::Big_1].HP == 0;
				nemos[NemoType::Small_2].isAlive = false;
				nemos[NemoType::Small_1].isAlive = false;
				nemos[NemoType::Big_1].isAlive = false;
			}
		}
#pragma endregion




		FireBullet(nemos);


#pragma region 적 충돌
		// 충돌확인
		if (IsCollision(nemos[NemoType::Small_1], nemos[NemoType::Big_2]))
		{
			decreaseHP(nemos[NemoType::Big_2]);

			nemos[NemoType::Small_1].isFire = false;
			nemos[NemoType::Small_1].posX = nemos[NemoType::Big_1].posX;
			nemos[NemoType::Small_1].posY = nemos[NemoType::Big_1].posY;

			SetNemoData(&nemos[NemoType::Small_1]);
			if (nemos[NemoType::Big_2].HP <= 0) {
				nemos[NemoType::Big_2].HP = 0;
				nemos[NemoType::Small_1].isAlive = false;
				nemos[NemoType::Big_2].isAlive = false;
				nemos[NemoType::Small_2].isAlive = false;
			}
		}
#pragma endregion



		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			nemos[NemoType::Small_1].isFire = true;
			break;
		case VK_UP:
			ProcessInputKey(wParam, nemos, controlID, notControlID);
			break;
		case VK_DOWN:
			ProcessInputKey(wParam, nemos, controlID, notControlID);
			break;
		case VK_LEFT:
			ProcessInputKey(wParam, nemos, controlID, notControlID);
			break;
		case VK_RIGHT:
			ProcessInputKey(wParam, nemos, controlID, notControlID);
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);

		break;
	case WM_PAINT:		// 윈도우 화면이 다시 그려지는 경우 발생하는 메시지
		hdc = BeginPaint(g_hWnd, &ps);

		wsprintf(text, "MousePosX : %d", mousePosX);
		TextOut(hdc, 200, 10, text, strlen(text));

		wsprintf(text, "MousePosY : %d", mousePosY);
		TextOut(hdc, 200, 40, text, strlen(text));

		wsprintf(text, "EnemyHP : %d", nemos[NemoType::Big_2].HP);
		TextOut(hdc, 200, 100, text, strlen(text));

		wsprintf(text, "EnemyHP : %d", nemos[NemoType::Big_1].HP);
		TextOut(hdc, 200, 800, text, strlen(text));

		DrawNemos(hdc, nemos);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:	// 닫기 버튼 메시지처리 (프로그램 종료)
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
