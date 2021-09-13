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
	//함수 호출 시점에 가상키가 어떤 상태인지 확인이 가능하다.
	/*
		1. 0x0000 (0000 0000 0000 0000) : 이전 프레임에 누른 적이 없고 호출시점에도 눌려있지 않다.
		2. 0x0001 (0000 0000 0000 0001) : 이전 프레임에 누른 적이 있고 호출시점에도 눌려있지 않다.
		3. 0x8000 (1000 0000 0000 0000) : 이전 프레임에 누른 적이 없고 호출시점에는 눌려있다.
		4. 0x8001 (1000 0000 0000 0001) : 이전 프레임에 누른 적이 있고 호출시점에는 눌려있다.

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
	//실습 1. 이 함수를 완성 해보자.
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
	//실습 2. 얘도 해보자
	if (GetAsyncKeyState(key) & 0x8000) {
		return true;
	}


	return false;
}
