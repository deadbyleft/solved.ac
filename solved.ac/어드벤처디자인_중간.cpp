
/*

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//int now = 0;

// visited�� ����� ���� �ٷ� node[current].second == true ó���Ѵ�.
// visited�� ������ ���� ���ٸ� ����Ŭ ������ �����Ǿ����� �� �� �ִ�.


void dfs(int current, vector <pair <int, bool>>& node, vector <pair <int, int>>& connected, vector<int>& visited
	, vector<int>& cycle, vector<bool>& node_used)
{
	bool same = false;

	int cycle_length = 0;

	static vector <pair <int, int>> t_size;

	if (node_used[current] == true)
		return;

	visited.push_back(current);

	for (int i = 0; i < visited.size(); i++)
		cout << visited[i] << " ";

	cout << endl;

	for (int i = 0; i < visited.size() - 1; i++)
	{
		if (current == visited[i])
			same = true;

		if (same == true)
		{
			cycle.push_back(visited[i]);
			cycle_length++;
		}
			
	}

	if (cycle_length == 2)
	{
		t_size.push_back(make_pair(current, visited[visited.size() - 2]));
	}

	for (int i = 0; i < t_size.size(); i++)
	{
		if (current == t_size[i].second && visited[visited.size() - 2 == t_size[i].first] ||
			current == t_size[i].first && visited[visited.size() - 2 == t_size[i].second])
			return;

		cout<< " [ " << t_size[i].first << ", " << t_size[i].second << " ] ";
	}
	
	cout << '\n';

	if (same == true)
	{
		cycle.push_back(current);
		cycle.push_back(-1);
		same = false;

		return;
	}

	if (node[current].second == false) // ���� �湮�� �� ���ٸ�
		node[current].second = true;

	for (int i = 0; i < connected.size(); i++) // �ش� ��尡 ����� ���� �ִ��� Ȯ��
	{
		if (connected[i].first == current) // ����� ��尡 �ִٸ�
		{
			dfs(connected[i].second, node, connected, visited, cycle, node_used);

			if (node_used[connected[i].second] == false)
				visited.pop_back();
		}

	}

}

int set_node(vector <pair <int, bool>>& node, vector<bool>& node_used)
{
	int node_num = 0;

	cout << "����� ������ �Է��Ͻÿ� : ";
	cin >> node_num;

	for (int i = 0; i < node_num; i++) // node_num ��ŭ ��带 �����Ѵ�
	{
		node_used.push_back(false);
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

	return connected_num;
}

void cal_cycle(int node_num, vector <pair <int, bool>>& node,
	vector <pair <int, int>>& connected, vector<int>& visited, vector<int>& cycle
	, vector<bool>& node_used)
{
	for (int i = 0; i < node_num; i++)
	{
		if (node[i].second == false)
		{
			dfs(i, node, connected, visited, cycle, node_used);
			visited.pop_back();

			for (int i = 0; i < node.size(); i++)
			{
				if (node[i].second == true)
					node_used[i] = true;
			}
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

	vector<bool> node_used;
	vector<int> visited;
	vector<int> cycle;

	int node_num = set_node(node, node_used);
	int connected_num = set_connected(connected);

	cal_cycle(node_num, node, connected, visited, cycle, node_used);
	print_result(cycle);

	return 0;
}

*/