#pragma once

// 싱글톤 패턴 : 프로그램에서 하나만 존재하는 객체가 필요할 때 사용되는 패턴
// 예시 ) 키매니저, 씬 매니저, 플레이어 데이터

// 장점 : 씬이나 객체를 가리지 않고 넘나들면서 데이터를 주고 받기 유용함
// 단점 : 싱글톤을 많이 쓰게 된다면 구조를 무너뜨릴 수 있음

template<typename T>
class Singleton
{
protected:
	static T* instance;		// static 멤버 변수

	Singleton() {};			// 생성자, 소멸자를 직접 호출하지 못하게 할거다.
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
