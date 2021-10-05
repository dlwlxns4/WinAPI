#pragma once
#include "Singleton.h"
#include "Config.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	// 자료구조 : vector 장점 : 크기를 가변적으로 바꿀 수 있다.
	//					 단점 : 삽입, 삭제가 필요하면 메모리 할당과 복사가 일어나서 속도가 저하된다.

	// 장점으로 빠른 속도가 필요한 자료구조가 필요
	// == map
	/* map : 장점 : 찾는 속도가 빠름
			 단점 : 자료구조 구현이 복잡하다.	
	*/
	map<string, Image*> mapImage; //  <Key, Value>


public:
	
	void Init();
	void Release();


	void AddImage(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = NULL); // File 프레임이 없는 이미지
	void AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = NULL); // File 프레임이 있는 이미지


	// 등록할 이미지 중에 필요한 이미지를 찾는 기능
	Image* FindImage(const char* fileName);
	// 사용이 종료된 이미지를 등록 해제하는 기능
	void DeleteImage(const char* fileName);
};

