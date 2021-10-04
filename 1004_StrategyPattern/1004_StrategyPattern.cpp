// 1004_StrategyPattern.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/*
    StratgyPattern 전략패턴
    - 알고리즘을 교첵 가능하게 하는 패턴. 
    - 알고리즘의 인터페이스를 정의하고, 각각의 클래스 별로 캡슐화한 후 사용한다.
    
    활용성
    - 행동들이 조금씩 다르고 개념적으로 관련된 클래스들이 많이 존재할 때.
    - 사용자가 몰라야 하는 데이터를 사용하는 알고리즘이 있을 때.
    - 하나의 클래스가 많은 행동을 정의하고, 이런 행동들이 그 클래스 안의 연산안에서 
      복잡한 다중 조건문의 모습을 가질 때.
        -> 많은 조건문 보다는 각각을 전략 패턴 클래스로 옮기는 것이 좋다.
    - 
*/


#include <iostream>

using namespace std;

// 정렬 알고리즘
// 버블 정렬, 삽입 정렬, 퀵 정렬, 합병 정렬, 카운팅 정렬 ...
//  -> 결과는 모두 같다.

class SortInterface
{
public:
    virtual void DoSort() = 0;     // 순수 가상함수
};

class BubbltSort : public SortInterface
{
public:
    virtual void DoSort() override { cout << "Do BubbleSort!"<<endl; };
};

class QuickSort : public SortInterface
{
public:
    virtual void DoSort() override { cout << "Do QuickSort!" << endl; };
};

class MergeSort : public SortInterface
{
public:
    virtual void DoSort() override { cout << "Do MergeSort!" << endl; };
};

class SortManager
{
private:
    SortInterface* sortAlgorithm=nullptr ;

public:
    void DoSort() { sortAlgorithm->DoSort();  }
    void ChangeSort(SortInterface* changeSort) 
    {  
        if (sortAlgorithm) delete sortAlgorithm;
        sortAlgorithm = changeSort;
    }
};

int main()
{
    SortManager sortManager;

    sortManager.ChangeSort(new QuickSort());
    sortManager.DoSort();

    sortManager.ChangeSort(new BubbltSort());
    sortManager.DoSort();

    sortManager.ChangeSort(new MergeSort());
    sortManager.DoSort();
}
