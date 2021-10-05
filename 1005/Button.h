#pragma once 
#include "Config.h"
#include "GameObject.h"

/*
함수 포인터

void ( *funPtr)(void); // 리턴 타입과 매개변수가 동일한 함수의 주소를 담을 수 있는 함수포인터
*/



class ButtonFunction;
//typedef void (ButtonFunction::*FuncPtr)(void);
typedef void (ButtonFunction::* FuncPtr)(ArgumentFuncPtr*);


enum class Button_State { None, Down, Up };		// FSM : Finite State Mach+ine : 유한 상태 기계
enum class Button_type {GotoBattle, GotoResult, Close};

class Button : public GameObject
{
private:
	Button_State state;
	Button_type type;
	ButtonFunction* bf;

	ArgumentFuncPtr* arg;


	FuncPtr pFunc;

public:
	virtual HRESULT Init() override;
	virtual HRESULT Init(int posX, int posY);
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetFunc(FuncPtr funcPtr, ButtonFunction* bf, ArgumentFuncPtr* arg) { this->pFunc = funcPtr; this->bf = bf; this->arg = arg; };
};

