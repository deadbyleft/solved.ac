
/*

#include <iostream>
#include <vector>

using namespace std;

vector<int> index;

void cal(int range, int length, int current_length, int current_num)
{
	if (current_num <= range && current_length < length) // ���� �� ä������ ���� ������
	{
		index.push_back(current_num);
	}

	if (current_length == length) // ���� ���� ä�����ٸ� ���
	{
		for (int i = 0; i < length; i++)
		{
			cout << index[i] << ' ';
		}

		cout << '\n';
		index.pop_back();
		return;
	}

	if (current_num > range) // ���� ���� �Ҹ�����
	{
		index.pop_back();
		return;
	}

	else
	{
		for (int i = current_num; i < range; i++)
			// ���� ���̿������� ������
		{
			cal(range, length, current_length + 1, i);
		}
	}
	
}

int main()
{
	int range = 0, length = 0;

	cin >> range >> length;

	cal(range, length, 0, 1);


}

*/