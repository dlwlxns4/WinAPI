#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);		// 권한이 굉장히 많은 총지배인

	// 빈 비트맵 생성
	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::Empty;
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// 새로 생성된 DC 
											// 기본적으로 Bitmap에 연결되어 있다.
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	//if (SUCCEEDED(E_FAIL))
	//{

	//}

	if (imageInfo->hBitmap == NULL)	// 비트맵 생성에 실패했을 때
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height,
		LR_LOADFROMFILE);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// 새로 생성된 DC 
											// 기본적으로 Bitmap에 연결되어 있다.
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDc);

		delete imageInfo;
		imageInfo = nullptr;
	}
}

void Image::Render(HDC hdc)
{


	BitBlt(hdc,				// 복사 목적지 DC
	0,				// 복사될 비트맵의 시작 위치 x
	0,				// 복사될 비트맵의 시작 위치 y
	imageInfo->width,	// 원본 복사할 가로 크기
	imageInfo->height,	// 원본 복사할 세로 크기
	imageInfo->hMemDc,	// 원본 DC
	0,					// 원본 비트맵 복사 시작 위치 x
	0,					// 원본 비트맵 복사 시작 위치 y
	SRCCOPY);			// 복사 옵션
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	// frameX : 0, frameY : 0 => 시작 (0, 0) 끝 (68,104)
	// frameX : 1, frameY : 0 => 시작 (68, 0) 끝 (68 ,104)
	// ... 반복
	
		
	if (isTransparent) {
		GdiTransparentBlt(hdc,
			destX - (imageInfo->width / 2),				// 복사될 비트맵의 시작 위치 x
			destY - (imageInfo->height / 2),				// 복사될 비트맵의 시작 위치 y
			(imageInfo->width / 9), (imageInfo->height / 1),

			imageInfo->hMemDc,
			(imageInfo->width /9) * frameX, (imageInfo->height / 1) * frameY,
			(imageInfo->width / 9), (imageInfo->height / 1)* (frameY+1),
			transColor
		);
	}
	else {
		BitBlt(hdc,				// 복사 목적지 DC
			destX - (imageInfo->width / 2),				// 복사될 비트맵의 시작 위치 x
			destY - (imageInfo->height / 2),				// 복사될 비트맵의 시작 위치 y
			imageInfo->width,	// 원본 복사할 가로 크기
			imageInfo->height,	// 원본 복사할 세로 크기
			imageInfo->hMemDc,	// 원본 DC
			0,					// 원본 비트맵 복사 시작 위치 x
			0,					// 원본 비트맵 복사 시작 위치 y
			SRCCOPY);			// 복사 옵션
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	COLORREF color = RGB(255, 0, 255);

	if (isTransparent) {
		GdiTransparentBlt(hdc,
			destX - (imageInfo->width / 2),				// 복사될 비트맵의 시작 위치 x
			destY - (imageInfo->height / 2),				// 복사될 비트맵의 시작 위치 y
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDc,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
			);
	}
	else {
		BitBlt(hdc,				// 복사 목적지 DC
			destX- (imageInfo->width / 2),				// 복사될 비트맵의 시작 위치 x
			destY- (imageInfo->height / 2),				// 복사될 비트맵의 시작 위치 y
			imageInfo->width,	// 원본 복사할 가로 크기
			imageInfo->height,	// 원본 복사할 세로 크기
			imageInfo->hMemDc,	// 원본 DC
			0,					// 원본 비트맵 복사 시작 위치 x
			0,					// 원본 비트맵 복사 시작 위치 y
			SRCCOPY);			// 복사 옵션
	}
}

