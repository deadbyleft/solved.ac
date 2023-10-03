


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void dfs(int current, vector <pair <int, bool>>& node, vector <pair <int, int>>& connected, vector<int>& visited, vector<int>& cycle)
{
	int next_node = 0;
	bool same = false;

	visited.push_back(current);

	if (node[current].second == false) // 아직 방문된 적 없다면
		node[current].second = true;


	for (int i = 0; i < connected.size(); i++) // 해당 노드가 연결된 값이 있는지 확인
	{

		if (connected[i].first == current) // 연결된 노드가 있다면
		{

			if (node[connected[i].second].second == false) // 연결된 노드의 좌표에 방문한 적 없다면
			{
				dfs(connected[i].second, node, connected, visited, cycle);
				visited.pop_back();
			}

			else // 이미 방문한 곳이라면 사이클 조건 만족 (같은 곳을 2번 방문한 곳이므로)
			{
				next_node = connected[i].second;

				for (int j = 0; j < visited.size(); j++)
				{
					if (visited[j] == next_node)
						same = true;

					if (same == true) // 연결된 노드의 다음 값을 찾았다면
						cycle.push_back(visited[j]); // 끝부분까지 전부 스택이므로 사이클에 입력
				}

				if (same == true) // 연결된 노드의 다음 좌표가 현재 스택에 존재한다면
				{
					if (cycle[cycle.size() - 2] == next_node) // 크기 2짜리인지 + 중복인지 확인 (1-3-1, 3-1-3 같은 경우 구분필요)
					{
						for (int i = 1; i < cycle.size() - 2; i++)
						{
							if (next_node == cycle[i] && cycle[cycle.size() - 1] == cycle[i - 1] && cycle[cycle.size() - 1] == cycle[i + 1])
							{
								same = false; // 중복이면 사이클 제거
								cycle.pop_back();
								cycle.pop_back();								 
							}
						}
					}

					if (same == true) // 중복이 아니라면 사이클 완성 후 '-1'로 분리
					{
						cycle.push_back(next_node);
						cycle.push_back(-1);
					}
					
				}


				else // 존재하지 않는다면 -> 계속 dfs 탐색
				{
					dfs(connected[i].second, node, connected, visited, cycle);
					visited.pop_back();
				}
			}
		}

	}

}

int set_node(vector <pair <int, bool>>& node)
{
	int node_num = 0;

	cout << "노드의 개수를 입력하시오 : ";
	cin >> node_num;

	for (int i = 0; i < node_num; i++) // node_num 만큼 노드를 생성한다
	{
		node.push_back(make_pair(i, false));
	}

	return node_num;
}

int set_connected(vector <pair <int, int>>& connected)
{
	int connected_num = 0, connect_before = 0, connect_after = 0;

	cout << "연결된 노드의 개수를 입력하시오 : ";
	cin >> connected_num;

	cout << '\n' << "[ 연결된 노드의 시작과 끝 값을 입력하시오 ] " << '\n' << '\n';

	for (int i = 0; i < connected_num; i++)
	{
		cin >> connect_before >> connect_after; // 연결된 노드의 값을 입력해준다
		connected.push_back(make_pair(connect_before, connect_after)); // 입력값을 바탕으로 연결된 노드값을 생성한다
	}

	//sort(connected.begin(), connected.end()); // 연결된 노드의 값을 connected.first 기준으로 오름차순 정렬한다

	return connected_num;
}

void cal_cycle(int node_num, vector <pair <int, bool>>& node,
	vector <pair <int, int>>& connected, vector<int>& visited, vector<int>& cycle)
{
	for (int i = 0; i < node_num; i++)
	{
		if (node[i].second == false)
		{
			dfs(i, node, connected, visited, cycle);
			visited.pop_back();
		}

	}
}

void print_result(vector<int>& cycle)
{
	int cycle_num = 0;

	cout << '\n' << "[ 사이클 목록 ] " << '\n';

	for (int i = 0; i < cycle.size(); i++)
	{
		if (cycle[i] == -1) // 한 사이클이 끝났으면 줄 띄우기
		{
			cout << '\n';
			cycle_num++;
		}
		else
			cout << cycle[i] << " ";
	}

	cout << '\n' << "총 사이클 개수는 " << cycle_num << "개입니다." << '\n';

}

int main()
{
	vector <pair <int, bool>> node; // node값 + 방문여부
	vector <pair <int, int>> connected;

	vector<int> visited;
	vector<int> cycle;

	int node_num = set_node(node);
	int connected_num = set_connected(connected);

	cout << endl << "여기서부터 dfs의 이동 동선입니다." << endl;

	cal_cycle(node_num, node, connected, visited, cycle);
	print_result(cycle);

	return 0;
}

