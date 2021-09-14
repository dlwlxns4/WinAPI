#include "image.h"

HRESULT image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	//�� ��Ʈ�� ����
	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::Empty;
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// ���� ������ DC �⺻������ Bitmap�� ����Ǿ� �ִ�.

	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL) {	//��Ʈ�� ������ ���� ���� ��
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
