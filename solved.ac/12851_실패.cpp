/*

#include <iostream>

using namespace std;

int index[100001] = { 0, };
int answer_var = 0;
int level = 1;
int goal = 0;
int now = 0;

bool ex_vector[100001] = { 0, };

int search(int now)
{

	for (int i = 1; i <= 100000; i++)
		if (index[i] == level)
		{
			if (i < 100000)
			{
				ex_vector[i + 1] = true;
				if (i + 1 == goal)
					answer_var++;
			}
								
			if (i >= 2)
			{
				ex_vector[i - 1] = true;
				if (i - 1 == goal)
					answer_var++;
			}

			if (i <= 50000)
			{
				ex_vector[i * 2] = true;
				if (i * 2 == goal)
					answer_var++;
			}
		}

	for (int i = 1; i <= 100000; i++)
		if (ex_vector[i])
			index[i] = level + 1;
		
	for (int i = 1; i <= 100000; i++)
		ex_vector[i] = false;

	if (answer_var != 0)
		return answer_var;
		
	return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> now >> goal;

	index[now] = 1;

	while (search(now) == 0)
		level++;

	cout << level << '\n' << answer_var;
}

*/