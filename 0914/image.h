#pragma once
#include "Config.h"

class image
{
public:
	enum ImageLoadType {
		Resource,			//프로그램에 포함되는 데이터
		File,				// 실행 시간에 외부에서 로드하는 데이터
		Empty,				// 빈 데이터
		End					// 길이 체크
	};


	// class와 struct의 문법적인 차이
	// 접근지정자가 public이냐 private이냐
	typedef struct tagImageInfo {
		HDC hMemDc;			// 이미지 데이터를 관리하는 핸들(메모리 관리자)
		HBITMAP hBitmap;	// 이미지 데이터
		HBITMAP hOldBit;	// 기존 이미지 데이터 
		int width;			// 가로 크기
		int height;			// 세로 크기
		BYTE loadType;		// 로드 타입

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
	HRESULT Init(int width, int height);						// 빈 비트맵 이미지 생성(LoadType : empty)
	void Init(const char* fileName, int width, int height);	// (LoadType : File)
	
	void Release();											// 메모리 해제

	void Render(HDC hdc);									// 이미지 데이터를 화면에 복사

};

