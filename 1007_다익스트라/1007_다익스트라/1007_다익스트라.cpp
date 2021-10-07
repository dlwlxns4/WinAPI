// 1007_다익스트라.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
	장점, 단점 : 모든 정점으로 이동하는 비용이 계산된다.
	8번 정점까지 이동하는 비용 : I

	인접 행렬 / 
	정점 갯수의 이차원 배열

	I=3000
	인접 리스트
*/


#include <iostream>
#include <vector>
#include <list>

#define I 3000
#define NodeCount 8

using namespace std;

int edgeCost[NodeCount][NodeCount] =
{
	{0, 2, I, I, I, 3, I, I},
	{2, 0, 4, 1, I, I, I, I},
	{I, 4, 0, I, 3, I, I, I},
	{I, 1, I, 0, 3, I, 2, I},
	{I, I, 3, 3, 0, I, I, 4},
	{3, I, I, I, I, 0, 7, I},
	{I, I, I, 2, I, 6, 0, 4},
	{I, I, I, I, 4, I, 4, 0},
};

int main()
{
	// 2번에서 출발 6번에 도착
	int startNode = 2;
	int destNode = 6;

	int currCost[NodeCount] = { I,I,I,I,I,I,I,I }; // 각 노드까지 이동하는데 드는 비용
	int prevNode[NodeCount] = { -1,-1,-1,-1,-1,-1,-1,-1 }; // 이전 노드 번호

	//방문 여부
	bool isVisited[NodeCount] = { false, false, false, false, false, false, false, false };

	currCost[startNode - 1] = 0;
	//isVisited[startNode - 1] = true;
	int currIndex = startNode - 1;


	cout << "1. 노드 번호\t현재 비용\t이전 노드  " << endl;

	for (int i = 0; i < NodeCount; i++)
		cout << i + 1 << "\t\t" << currCost[i] << "\t\t" << prevNode[i] + 1 << endl;


	for (int j = 0; j < NodeCount; j++)
	{
		int minIndex = -1;
		int minCost = I;
		//갱신된 노드들 중에서 현재 비용이 가장 적은 노드를 찾는다.
		for (int i = 0; i < NodeCount; i++)
		{
			if (isVisited[i]) continue;

			if (minCost > currCost[i])
			{
				minCost = currCost[i];
				minIndex = i;
			}
		}

		currIndex = minIndex;

		for (int i = 0; i < NodeCount; i++)
		{
			if (i != currIndex)
			{
				//// 현재노드(2)를 통해서 해당 노드에 이동했을 때의 비용 계산
				//currCost[currIndex] + edgeCost[currIndex][i];

				//// 해당 노드의 계산된 이동비용보다 작으면 값을 갱신한다.
				//currCost[i];

				if (currCost[currIndex] + edgeCost[currIndex][i] < currCost[i])
				{
					currCost[i] = currCost[currIndex] + edgeCost[currIndex][i];
					prevNode[i] = currIndex;
				}
			}
		}
		isVisited[minIndex] = true;
	cout << endl;
	cout << "2. 노드 번호\t현재 비용\t이전 노드  " << endl;
	for (int i = 0; i < NodeCount; i++)
		cout << i + 1 << "\t\t" << currCost[i] << "\t\t" << prevNode[i] + 1 << endl;
	}


	int i = 5;
	vector<int> path;
	while (true)
	{
		if (prevNode[i - 1] + 1 == startNode)
		{
			path.push_back(i);
			path.push_back(prevNode[i - 1] + 1);
			break;
		}

		path.push_back(i);
		i = prevNode[i-1]+1;
	}
	reverse(path.begin(), path.end());
	for (int i : path)
		cout << i << "->";
	
}