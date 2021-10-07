

#include <iostream>
#include <vector>

using namespace std;

typedef struct tagHumanInfo
{
	int id;
	int infoCount;
	vector<int> info;
	bool isHuman=false;
} HUMAN_INFO;

void CheckHuamn(vector<HUMAN_INFO>& humanDatas)
{
	//큐 (선입 선출) / 스택 (후입 선출)

	// 너비우선탐색, 깊이우선탐색

	vector<HUMAN_INFO*> queue;
	queue.push_back(&(humanDatas[0]));
	humanDatas[0].isHuman = true;

	int answer;

	while (!queue.empty())
	{
		HUMAN_INFO* info = queue.front();
		queue.erase(queue.begin());

		for (int i = 0; i < info->infoCount; i++)
		{
			answer = info->info[i]-1;
			if (humanDatas[answer].isHuman != true)
			{
				humanDatas[answer].isHuman = true;
				queue.push_back(&(humanDatas[answer]));
			
			}
		}
	}

}

int main()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "마을1.txt", "r");


	vector<HUMAN_INFO> humanDatas;

	
	if(fp!=nullptr)
	{
		int totalCount;
		fscanf_s(fp, "%d", &totalCount);

		humanDatas.resize(totalCount);

		while (true)
		{
			if (feof(fp))
				break;

			int id,humanIndex;
			fscanf_s(fp, "%d", &id);
			humanIndex = id - 1;
			humanDatas[humanIndex].id = id;

			fscanf_s(fp, "%d", &(humanDatas[humanIndex].infoCount));
			humanDatas[humanIndex].info.resize(humanDatas[humanIndex].infoCount);

			int info;
			for (int i = 0; i < humanDatas[humanIndex].infoCount; i++)
			{
				fscanf_s(fp, "%d", &(humanDatas[humanIndex].info[i]));
			}
		}

		fclose(fp);
	}
	CheckHuamn(humanDatas);

	int trueHumanCount = 0;
	for (auto human : humanDatas)
	{
		if (human.isHuman)
			trueHumanCount++;
	}
	cout << trueHumanCount << endl;
}

