#include "image.h"

HRESULT image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	//빈 비트맵 생성
	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::Empty;
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// 새로 생성된 DC 기본적으로 Bitmap에 연결되어 있다.

	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {	//비트맵 생성에 실패 했을 때
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void image::Init(const char* fileName, int width, int height)
{
}

void image::Release()
{
	if (imageInfo) {
		SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDc);

		delete imageInfo;
		imageInfo = nullptr;
	}

}

void image::Render(HDC hdc)
{
}
