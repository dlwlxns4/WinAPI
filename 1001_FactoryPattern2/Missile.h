#pragma once
class Missile		// interface
{
private:
	// �������

public:
	// ����Լ�
	virtual void Move() = 0;		// �����Լ� / <���������Լ�>
	virtual void Notice() = 0;		// �̻��� ���� �� �˸�

	Missile() {}
	virtual ~Missile();
};

// �̻��� 1) �߻�� ���� ������ ���ư��� �̻���
class NormalMissile : public Missile
{
public:
	virtual void Move() override;
	virtual void Notice() override;

	NormalMissile() {}
	virtual ~NormalMissile();
};

// �̻��� 2) ����ź Ÿ���� ���� �� Ÿ���� ��ġ�� �ǽð����� �����ϴ� �̻���
class HommingMissile : public Missile
{
public:
	virtual void Move() override;
	virtual void Notice() override;

	HommingMissile() {}
	virtual ~HommingMissile();
};

// �̻��� 3) �߻�� �� �����ð� ���Ŀ� 36���� �����ϴ� �̻���
class FireworkMissile : public Missile
{
	/*Missile* m;*/
public:
	virtual void Move() override;
	virtual void Notice() override;

	FireworkMissile() {}
	virtual ~FireworkMissile();	// __vfptr �� (�����Լ����̺�) �߰��ȴ�.
};

