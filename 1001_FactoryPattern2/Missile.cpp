#include "Missile.h"
#include <string>
#include <iostream>

using namespace std;

void NormalMissile::Move()
{
	cout << "�̻����� �������� ���ư���~" << endl;
}

void NormalMissile::Notice()
{
	cout << "�Ϲ� �̻����� �����Ǿ��� !" << endl;
}

NormalMissile::~NormalMissile()
{
	cout << "�Ϲ� �̻��� ���� !" << endl;
}

void HommingMissile::Move()
{
	cout << "�̻����� Ÿ���� ���� ���ư���~" << endl;
}

void HommingMissile::Notice()
{
	cout << "���� �̻����� �����Ǿ��� !" << endl;
}

HommingMissile::~HommingMissile()
{
	cout << "���� �̻��� ���� !" << endl;
}

void FireworkMissile::Move()
{
	cout << "���� �ð� �Ŀ� ���ҵȴ� !" << endl;
}

void FireworkMissile::Notice()
{
	cout << "���� �̻����� �����Ǿ��� !" << endl;
}

FireworkMissile::~FireworkMissile()
{
	cout << "���� �̻��� ���� !" << endl;
}

Missile::~Missile()
{
	cout << "�̻��� ���� !" << endl;
}
