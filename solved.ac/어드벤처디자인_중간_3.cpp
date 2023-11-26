/*


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int Check_SameCycle(queue<int> cycle_save, vector<int> cycle)
{
	bool Same_exist = false;

	if (cycle.size() > cycle_save.size())
	{
		for (int i = 0; i < cycle.size() - cycle_save.size(); i++)
		{
			Same_exist = false;

			for (int j = 0; j < cycle_save.size(); j++)
			{
				if (cycle_save.front() != cycle[i + j])
					Same_exist = true;

				cycle_save.push(cycle_save.front());
				cycle_save.pop();
			}

			if (Same_exist == false)
				return false;
		}
	}

	return true;
}

void dfs_FindCycle(int current, vector <pair <int, bool>>& index, vector <pair <int, int>>& connected, vector<int>& visited
	, vector<int>& cycle, vector<bool>& index_used, queue<int>& cycle_save)
{
	bool same = false;

	//static vector <pair <int, int>> t_size;

	if (index_used[current] == true)
		return;

	visited.push_back(current);

	for (int i = 0; i < visited.size() - 1; i++)
	{
		if (current == visited[i])
			same = true;

		if (same == true)
			cycle_save.push(visited[i]);
	}

	if (same == true)
	{
		if (Check_SameCycle(cycle_save, cycle))
		{
			for (int i = cycle_save.size(); i > 0; i--)
			{
				cycle.push_back(cycle_save.front());
				cycle_save.pop();
			}

			cycle.push_back(current);
			cycle.push_back(-1);
		}

		else
		{
			while (!cycle_save.empty())
				cycle_save.pop();
		}


		same = false;
		return;
	}

	if (index[current].second == false) // ���� �湮�� �� ���ٸ�
		index[current].second = true;

	for (int i = 0; i < connected.size(); i++) // �ش� ��尡 ����� ���� �ִ��� Ȯ��
	{
		if (connected[i].first == current) // ����� ��尡 �ִٸ�
		{
			dfs_FindCycle(connected[i].second, index, connected, visited, cycle, index_used, cycle_save);

			if (index_used[connected[i].second] == false)
				visited.pop_back();
		}

	}

}



int set_index(vector <pair <int, bool>>& index, vector<bool>& index_used)
{
	int node_num = 0;

	cout << "����� ������ �Է��Ͻÿ� : ";
	cin >> node_num;

	for (int i = 0; i < node_num; i++) // node_num ��ŭ ��带 �����Ѵ�
	{
		index_used.push_back(false);
		index.push_back(make_pair(i, false));
	}

	return node_num;
}

int set_connected(vector <pair <int, int>>& connected)
{
	int connected_num = 0, connect_before = 0, connect_after = 0;

	cout << "���� ������ �Է��Ͻÿ� : ";
	cin >> connected_num;

	cout << '\n' << "[ ����� ����� ���۰� �� ���� �Է��Ͻÿ� ] " << '\n' << '\n';

	for (int i = 0; i < connected_num; i++)
	{
		cin >> connect_before >> connect_after; // ����� ����� ���� �Է����ش�
		connected.push_back(make_pair(connect_before, connect_after)); // �Է°��� �������� ����� ��尪�� �����Ѵ�
	}

	sort(connected.begin(), connected.end()); // ����� ����� ���� connected.first �������� �������� �����Ѵ�

	return connected_num;
}

void cal_cycle(int node_num, vector <pair <int, bool>>& index,
	vector <pair <int, int>>& connected, vector<int>& visited, vector<int>& cycle
	, vector<bool>& index_used, queue<int>& cycle_save)
{
	for (int i = 0; i < node_num; i++)
	{
		if (index[i].second == false)
		{
			dfs_FindCycle(i, index, connected, visited, cycle, index_used, cycle_save);
			visited.pop_back();

			for (int i = 0; i < index.size(); i++)
			{
				if (index[i].second == true)
					index_used[i] = true;
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
	vector <pair <int, bool>> index; // index�� + �湮����
	vector <pair <int, int>> connected;

	vector<bool> index_used;
	vector<int> visited;
	vector<int> cycle;
	queue<int> cycle_save;

	int node_num = set_index(index, index_used);
	int connected_num = set_connected(connected);

	cal_cycle(node_num, index, connected, visited, cycle, index_used, cycle_save);
	print_result(cycle);

	return 0;
}


/*

0 2
2 4
4 3
3 1
3 0
4 2
1 3
0 1

0 1
1 2
2 3
3 0
0 2
5 7
7 6
6 4
3 1


*/