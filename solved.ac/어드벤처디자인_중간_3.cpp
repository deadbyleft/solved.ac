


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void dfs(int current, vector <pair <int, bool>>& node, vector <pair <int, int>>& connected, vector<int>& visited, vector<int>& cycle)
{
	int next_node = 0;
	bool same = false;

	visited.push_back(current);

	if (node[current].second == false) // ���� �湮�� �� ���ٸ�
		node[current].second = true;


	for (int i = 0; i < connected.size(); i++) // �ش� ��尡 ����� ���� �ִ��� Ȯ��
	{

		if (connected[i].first == current) // ����� ��尡 �ִٸ�
		{

			if (node[connected[i].second].second == false) // ����� ����� ��ǥ�� �湮�� �� ���ٸ�
			{
				dfs(connected[i].second, node, connected, visited, cycle);
				visited.pop_back();
			}

			else // �̹� �湮�� ���̶�� ����Ŭ ���� ���� (���� ���� 2�� �湮�� ���̹Ƿ�)
			{
				next_node = connected[i].second;

				for (int j = 0; j < visited.size(); j++)
				{
					if (visited[j] == next_node)
						same = true;

					if (same == true) // ����� ����� ���� ���� ã�Ҵٸ�
						cycle.push_back(visited[j]); // ���κб��� ���� �����̹Ƿ� ����Ŭ�� �Է�
				}

				if (same == true) // ����� ����� ���� ��ǥ�� ���� ���ÿ� �����Ѵٸ�
				{
					if (cycle[cycle.size() - 2] == next_node) // ũ�� 2¥������ + �ߺ����� Ȯ�� (1-3-1, 3-1-3 ���� ��� �����ʿ�)
					{
						for (int i = 1; i < cycle.size() - 2; i++)
						{
							if (next_node == cycle[i] && cycle[cycle.size() - 1] == cycle[i - 1] && cycle[cycle.size() - 1] == cycle[i + 1])
							{
								same = false; // �ߺ��̸� ����Ŭ ����
								cycle.pop_back();
								cycle.pop_back();								 
							}
						}
					}

					if (same == true) // �ߺ��� �ƴ϶�� ����Ŭ �ϼ� �� '-1'�� �и�
					{
						cycle.push_back(next_node);
						cycle.push_back(-1);
					}
					
				}


				else // �������� �ʴ´ٸ� -> ��� dfs Ž��
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

	cout << "����� ������ �Է��Ͻÿ� : ";
	cin >> node_num;

	for (int i = 0; i < node_num; i++) // node_num ��ŭ ��带 �����Ѵ�
	{
		node.push_back(make_pair(i, false));
	}

	return node_num;
}

int set_connected(vector <pair <int, int>>& connected)
{
	int connected_num = 0, connect_before = 0, connect_after = 0;

	cout << "����� ����� ������ �Է��Ͻÿ� : ";
	cin >> connected_num;

	cout << '\n' << "[ ����� ����� ���۰� �� ���� �Է��Ͻÿ� ] " << '\n' << '\n';

	for (int i = 0; i < connected_num; i++)
	{
		cin >> connect_before >> connect_after; // ����� ����� ���� �Է����ش�
		connected.push_back(make_pair(connect_before, connect_after)); // �Է°��� �������� ����� ��尪�� �����Ѵ�
	}

	//sort(connected.begin(), connected.end()); // ����� ����� ���� connected.first �������� �������� �����Ѵ�

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

	cout << '\n' << "[ ����Ŭ ��� ] " << '\n';

	for (int i = 0; i < cycle.size(); i++)
	{
		if (cycle[i] == -1) // �� ����Ŭ�� �������� �� ����
		{
			cout << '\n';
			cycle_num++;
		}
		else
			cout << cycle[i] << " ";
	}

	cout << '\n' << "�� ����Ŭ ������ " << cycle_num << "���Դϴ�." << '\n';

}

int main()
{
	vector <pair <int, bool>> node; // node�� + �湮����
	vector <pair <int, int>> connected;

	vector<int> visited;
	vector<int> cycle;

	int node_num = set_node(node);
	int connected_num = set_connected(connected);

	cout << endl << "���⼭���� dfs�� �̵� �����Դϴ�." << endl;

	cal_cycle(node_num, node, connected, visited, cycle);
	print_result(cycle);

	return 0;
}

