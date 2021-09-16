#pragma once
#include "Config.h"

class Image
{
public:
	enum ImageLoadType
	{
		Resource,		// ���α׷��� ���ԵǴ� ������
		File,			// ���� �ð��� �ܺο��� �ε��ϴ� ������
		Empty,			// �� ��Ʈ�� �̹��� ����
		End
	};

	// class�� struct�� �������� ����
	// ���������ڰ� public�̳� private�̳�
	typedef struct tagImageInfo
	{
		HDC hMemDc;		// �̹��� �����͸� �����ϴ� �ڵ�(�޸� ������)
		HBITMAP hBitmap;// �̹��� ������
		HBITMAP hOldBit;// ���� �̹��� ������
		int width;		// ���� ũ��
		int height;		// ���� ũ��
		BYTE loadType;	// �ε� Ÿ��

		tagImageInfo()
		{
			hMemDc = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = ImageLoadType::Empty;
		};
	} IMAGE_INFO, *LPIMAGE_INFO;

	//struct testImageInfo : public tagImageInfo
	//{

	//};

	//tagImageInfo imageInfo;
	//IMAGE_INFO imageInfo2;

	//tagImageInfo* imageInfo;
	//LPIMAGE_INFO imageInfo3;

private:
	LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

public:
	HRESULT Init(int width, int height);	// �� ��Ʈ�� �̹��� ����(Empty)
	HRESULT Init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = NULL); // File

	void Release();	// �޸� ����

	void Render(HDC hdc, int destX, int destY, int frameX, int framY);	// �̹��� �����͸� ȭ�鿡 
	void Render(HDC hdc, int destX, int destY);	// �̹��� �����͸� ȭ�鿡 
	void Render(HDC hdc);	// �̹��� �����͸� ȭ�鿡 ����

	HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDc; }
};

