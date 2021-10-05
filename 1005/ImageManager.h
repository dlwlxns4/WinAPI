#pragma once
#include "Singleton.h"
#include "Config.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	// �ڷᱸ�� : vector ���� : ũ�⸦ ���������� �ٲ� �� �ִ�.
	//					 ���� : ����, ������ �ʿ��ϸ� �޸� �Ҵ�� ���簡 �Ͼ�� �ӵ��� ���ϵȴ�.

	// �������� ���� �ӵ��� �ʿ��� �ڷᱸ���� �ʿ�
	// == map
	/* map : ���� : ã�� �ӵ��� ����
			 ���� : �ڷᱸ�� ������ �����ϴ�.	
	*/
	map<string, Image*> mapImage; //  <Key, Value>


public:
	
	void Init();
	void Release();


	void AddImage(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = NULL); // File �������� ���� �̹���
	void AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = NULL); // File �������� �ִ� �̹���


	// ����� �̹��� �߿� �ʿ��� �̹����� ã�� ���
	Image* FindImage(const char* fileName);
	// ����� ����� �̹����� ��� �����ϴ� ���
	void DeleteImage(const char* fileName);
};

