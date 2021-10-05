#pragma once 
#include "Config.h"
#include "GameObject.h"

/*
�Լ� ������

void ( *funPtr)(void); // ���� Ÿ�԰� �Ű������� ������ �Լ��� �ּҸ� ���� �� �ִ� �Լ�������
*/



class ButtonFunction;
//typedef void (ButtonFunction::*FuncPtr)(void);
typedef void (ButtonFunction::* FuncPtr)(ArgumentFuncPtr*);


enum class Button_State { None, Down, Up };		// FSM : Finite State Mach+ine : ���� ���� ���
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

