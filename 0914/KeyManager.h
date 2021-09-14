#pragma once
#include "Config.h"
#include <bitset> // stl 자료구조 
#include "SingleTon.h"


#define KEY_MAX_COUNT 256

using namespace std;

class KeyManager : public Singleton<KeyManager>
{
private:
	// 멤버 변수 (데이터 타입, 자료 구조)
	
	bitset<KEY_MAX_COUNT> keyUp;		// 키가 안 눌린 상태인지 아닌지 저장
	bitset<KEY_MAX_COUNT> keyDown;		// 키가 눌린 상태인지 아닌지 저장
	

public:
	void Init();
	
	bool IsOnceKeyDown(int key);		// 키가 첫 번째로 눌렸는지 판단
	bool IsOnceKeyUp(int key);			// 키가 첫 번째로 눌렸다가 떨어졌는지 판단
	bool IsStayKeyDown(int key);		// 키가 눌려서 있는 지 판단
};