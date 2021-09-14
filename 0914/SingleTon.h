#pragma once

// �̱��� ���� : ���α׷����� �ϳ��� �����ϴ� ��ü�� �ʿ��� �� ���Ǵ� ����
// ���� ) Ű�Ŵ���, �� �Ŵ���, �÷��̾� ������

// ���� : ���̳� ��ü�� ������ �ʰ� �ѳ���鼭 �����͸� �ְ� �ޱ� ������
// ���� : �̱����� ���� ���� �ȴٸ� ������ ���ʶ߸� �� ����

template<typename T>
class Singleton
{
protected:
	static T* instance;		// static ��� ����

	Singleton() {};			// ������, �Ҹ��ڸ� ���� ȣ������ ���ϰ� �ҰŴ�.
	~Singleton() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();
	void SetData(T data);

};

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T* Singleton<T>::GetSingleton()
{
	if (!instance){
		instance = new T;
	}

	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

template<typename T>
inline void Singleton<T>::SetData(T data)
{
	instance = data;
}
