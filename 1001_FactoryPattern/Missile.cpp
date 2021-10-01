#include "Missile.h"
#include <string>
#include <iostream>

using namespace std;

void NormalMissile::Move()
{
	cout << "미사일이 직선으로 날아간다~" << endl;
}

void NormalMissile::Notice()
{
	cout << "일반 미사일이 생성되었다 !" << endl;
}

NormalMissile::~NormalMissile()
{
	cout << "일반 미사일 삭제 !" << endl;
}

void HommingMissile::Move()
{
	cout << "미사일이 타겟을 향해 날아간다~" << endl;
}

void HommingMissile::Notice()
{
	cout << "유도 미사일이 생성되었다 !" << endl;
}

HommingMissile::~HommingMissile()
{
	cout << "유도 미사일 삭제 !" << endl;
}

void FireworkMissile::Move()
{
	cout << "일정 시간 후에 분할된다 !" << endl;
}

void FireworkMissile::Notice()
{
	cout << "폭죽 미사일이 생성되었다 !" << endl;
}

FireworkMissile::~FireworkMissile()
{
	cout << "폭죽 미사일 삭제 !" << endl;
}

Missile::~Missile()
{
	cout << "미사일 삭제 !" << endl;
}
