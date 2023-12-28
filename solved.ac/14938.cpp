/*

#include <iostream>


using namespace std;

int connected[101][101] = { 0, };
int land_score[101] = { 0, };
bool visited[101] = { 0, };

int max_num = 0;
int answer = 0;

// visited()는 매 탐색때마다 초기화되어야한다

void dfs(int now, int able_search)
{
	

	for (int i = 1; i <= 100; i++)
	{
		if (connected[now][i] != 0 && able_search >= connected[now][i])
		{
			if (!visited[now])
			{
				visited[now] = true;
				max_num += land_score[i];
			}
				
			dfs(i, able_search - connected[now][i]);
		}
	}
		
	return;
}

int main()
{
	int land_num = 0;
	int able_search = 0;
	int way_num = 0;
	int way_before = 0;
	int way_after = 0;
	int way_length = 0;

	cin >> land_num >> able_search >> way_num;

	for (int i = 1; i <= land_num; i++)
		cin >> land_score[i];

	for (int i = 1; i <= way_num; i++)
	{
		cin >> way_before >> way_after >> way_length;
		connected[way_before][way_after] = way_length;
		connected[way_after][way_before] = way_length;
	}

	for (int i = 1; i <= land_num; i++)
	{
		max_num += land_score[i];
		dfs(i, able_search);

		if (max_num > answer)
			answer = max_num;

		for (int i = 1; i <= 100; i++)
			visited[i] = false;

		max_num = 0;
	}
		

	cout << answer;
		
}

*/