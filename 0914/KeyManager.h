#pragma once
#include "Config.h"
#include <bitset> // stl �ڷᱸ�� 
#include "SingleTon.h"


#define KEY_MAX_COUNT 256

using namespace std;

class KeyManager : public Singleton<KeyManager>
{
private:
	// ��� ���� (������ Ÿ��, �ڷ� ����)
	
	bitset<KEY_MAX_COUNT> keyUp;		// Ű�� �� ���� �������� �ƴ��� ����
	bitset<KEY_MAX_COUNT> keyDown;		// Ű�� ���� �������� �ƴ��� ����
	

public:
	void Init();
	
	bool IsOnceKeyDown(int key);		// Ű�� ù ��°�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key);			// Ű�� ù ��°�� ���ȴٰ� ���������� �Ǵ�
	bool IsStayKeyDown(int key);		// Ű�� ������ �ִ� �� �Ǵ�
};