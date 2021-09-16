#include "KeyManager.h"

void KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++) {
		keyUp[i] = true;
		keyDown[i] = false;
	}
}

bool KeyManager::IsOnceKeyDown(int key)
{
	//�Լ� ȣ�� ������ ����Ű�� � �������� Ȯ���� �����ϴ�.
	/*
		1. 0x0000 (0000 0000 0000 0000) : ���� �����ӿ� ���� ���� ���� ȣ��������� �������� �ʴ�.
		2. 0x0001 (0000 0000 0000 0001) : ���� �����ӿ� ���� ���� �ְ� ȣ��������� �������� �ʴ�.
		3. 0x8000 (1000 0000 0000 0000) : ���� �����ӿ� ���� ���� ���� ȣ��������� �����ִ�.
		4. 0x8001 (1000 0000 0000 0001) : ���� �����ӿ� ���� ���� �ְ� ȣ��������� �����ִ�.

	*/

	if (GetAsyncKeyState(key) & 0x8000 ) {
		if (!keyDown[key]) {
			keyDown[key] = true;
			return true;
		}
	}
	else {
		keyDown[key] = false;
	}
	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	//�ǽ� 1. �� �Լ��� �ϼ� �غ���.
	if (GetAsyncKeyState(key) & 0x8000) {
		keyUp[key] = false;
	}
	else {
		if (!keyUp[key]) {
			keyUp[key] = true;
			return true;
		}
	}
	return false;
	
}

bool KeyManager::IsStayKeyDown(int key)
{
	//�ǽ� 2. �굵 �غ���
	if (GetAsyncKeyState(key) & 0x8000) {
		return true;
	}


	return false;
}