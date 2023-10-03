/*


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair <int, int>> connected;
vector<bool> visited;
vector<int> cycle;
vector<int> cycle_saved;

// connected �迭�� �̿��Ͽ� ��Ʈ�� Ȯ���Ѵ�.
// ��Ʈ�� visited�� ���� �� cycle�̸� ���� cycle�� �����Ѵ�



void dfs(int current)
{
	visited[current] = true; // current��° ���� �湮��

	for (int i = 0; i < connected.size(); i++)
	{
		if (connected[i].first == current) // ���簪���� �ٸ� ���� �� �� ���� ���
		{
			for (int i = 0; i < cycle.size(); i++)
			{
				if (connected[i].second == cycle[i]) // �ش� ��� �湮���� ����Ŭ�� �����ȴٸ�
				{
					for (int i = 0; i < cycle.size(); i++) // �ش� ����Ŭ cycle_saved�� ����
					{
						cycle_saved.push_back(cycle[i]);
					}
					cycle_saved.push_back(-1);
				}
			}

			if (!visited[connected[i].second]) // ����� ��尪�� �湮�� ���� ���ٸ�
			{
				cycle.push_back(i); // connected[i] ����

				dfs(connected[i].second); // ����Լ� ����
			}				
		}
	}

	if (cycle.size() > 0) // �� ���ǹ� ���ٸ� ���� (ũ�Ⱑ 0�̾ pop ����ǹǷ�)
		cycle.pop_back(); // �� ���ƺôٸ� pop
}



int main()
{
	int node_num = 0, cycle_num = 0, connected_num = 0,
		connect_before = 0, connect_after = 0;

	cin >> node_num >> connected_num;

	for (int i = 0; i < node_num; i++)
	{
		visited.push_back(false);
	}	

	for (int i = 0; i < connected_num; i++)
	{
		cin >> connect_before >> connect_after; // ����� ����� ���� �Է����ش�
		connected.push_back(make_pair(connect_before, connect_after)); // ��� ����
		
	}

	for (int i = 0; i < node_num; i++)
	{
		dfs(i);
	}

	for (int i = 0; i < cycle_saved.size(); i++)
	{
		if (cycle_saved[i] == -1)
			cout << endl;
		else
		{
			cout << connected[cycle_saved[i]].first << " " <<
				connected[cycle_saved[i]].second << " ";
		}
			
	}


}

*/