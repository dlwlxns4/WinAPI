﻿// 211001_FactoryPattern.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/*
	UML 에서 제공하는 클래스들 간의 관계 표현

	1) 연관 관계 (실선, 화살표) : 클래스들 개념 상 서로 연결되어 있다.
								한 클래스에서 다른 클래스의 기능을 사용하는 경우

	2) 일반화 관계 ( 속이 빈 화살표 ) : 객체지향개념에서 상속 관계를 표현하는 경우

	3) 집합 관계 : 클래스들 사이의 전체 또는 부분으로 구성된 관계
		3-1) 집약관계 ( 속이 빈 다이아몬드 ) : 전체 객체(탱크)의 라이프타임과 부분 객체(탑승자)의 라이프타임이 독립적
		3-2) 합성관계 ( 속이 찬 다이아몬드 ) : 전체 객체(탱크)의 라이프타임과 부분 객체 (포신, 몸통, 바퀴)의 라이프타임이 의존적

	4) 의존 관계 (점선 화살표) : 연관 관계와 같이 한 클래스가 다른 클래스에서 제공하는 기능을 사용할 때
								( 차이점 : 매우 짧은 시간동안 유지되는 경우 )

	5) 실체화 관계 (빈 삼각형과 점선) : 인터페이스와 실체(실제로 구현한 클래스) 사이의 관계를 표현
*/

/*
	UML 클래스 다이어그램 복습
	추상팩토리 패턴 조사 + 노션추가
*/

#include <iostream>
#include "MissileFactory.h"

int main()
{
	MissileFactory* mf[3];

	mf[0] = new NormalMissileFactory;
	mf[1] = new HommingMissileFactory;
	mf[2] = new FireworkMissileFactory;

	for (int i = 0; i < 3; i++)
	{
		mf[i]->NewMissile();
	}


}