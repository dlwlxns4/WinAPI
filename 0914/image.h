#pragma once
#include "Config.h"

class image
{
public:
	enum ImageLoadType {
		Resource,			//���α׷��� ���ԵǴ� ������
		File,				// ���� �ð��� �ܺο��� �ε��ϴ� ������
		Empty,				// �� ������
		End					// ���� üũ
	};


	// class�� struct�� �������� ����
	// ���������ڰ� public�̳� private�̳�
	typedef struct tagImageInfo {
		HDC hMemDc;			// �̹��� �����͸� �����ϴ� �ڵ�(�޸� ������)
		HBITMAP hBitmap;	// �̹��� ������
		HBITMAP hOldBit;	// ���� �̹��� ������ 
		int width;			// ���� ũ��
		int height;			// ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

		tagImageInfo() {
			hMemDc = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = ImageLoadType::Empty;
		}
	}IMAGE_INFO, *LPIMAGE_INFO; 


private:
	IMAGE_INFO *imageInfo;

public:
	HRESULT Init(int width, int height);						// �� ��Ʈ�� �̹��� ����(LoadType : empty)
	void Init(const char* fileName, int width, int height);	// (LoadType : File)
	
	void Release();											// �޸� ����

	void Render(HDC hdc);									// �̹��� �����͸� ȭ�鿡 ����

};

