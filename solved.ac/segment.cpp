
/*


#include <iostream>
#include <vector>

using namespace std;

vector <int> list;
vector <int> seg_tree;



int construct_tree(vector<int>& list, vector<int>& seg_tree, int start, int end, int current)
{
	int mid = start + (end - start) / 2;
	int child = 2 * current;

	if (start == end)
	{
		seg_tree[current] = list[start];
		return list[start];
	}

	seg_tree[current] = construct_tree(list, seg_tree, start, mid, child + 1)
		+ construct_tree(list, seg_tree, mid + 1, end, child + 2);

	return seg_tree[current];
}

int query_sum(vector<int>& seg_tree, int start, int end, int q_s, int q_e, int current)
{

	int mid = start + (end - start) / 2;
	int child = 2 * current;

	if (q_s <= start && q_e >= end) return seg_tree[current];
	if (end<q_s || start>q_e) return 0;

	return query_sum(seg_tree, start, mid, q_s, q_e, child + 1) +
		query_sum(seg_tree, mid + 1, end, q_s, q_e, child + 2);
}

int construct_list(vector<int>& list, vector<int>& seg_tree, int t_size)
{
	int num = 0, size = 1;

	cout << "�Է� ����Ʈ�� ũ�⸦ �Է��Ͻÿ� : ";
	cin >> t_size;
	cout << "\n�Է� ����Ʈ�� �� ���� �Է��Ͻÿ� : ";

	for (int i = 0; i < t_size; i++)
	{
		cin >> num;
		list.push_back(num); // �Է¸���Ʈ�� �� ���� �Է¹޴´�
	}

	while (t_size * 2 > size)
	{
		size *= 2; // ���׸�Ʈ Ʈ���� ũ�Ⱑ ������ȭƮ�� ���°� �ǵ��� �����Ѵ�
	}


	for (int i = 0; i < size; i++)
	{
		seg_tree.push_back(0); // �Է¹��� ũ�⸸ŭ ���׸�Ʈ Ʈ���� �����Ѵ�
	}

	construct_tree(list, seg_tree, 0, t_size - 1, 0);

	return t_size;
}

int segtree_update(vector<int>& seg_tree, int start, int end, int i,
	int d_value, int current)
{

	int mid = start + (end - start) / 2;
	int child = 2 * current;

	if (i<start || i>end) return NULL;

	seg_tree[current] = seg_tree[current] + d_value;

	if (start != end)
	{
		segtree_update(seg_tree, start, mid, i, d_value, child + 1);
		segtree_update(seg_tree, mid + 1, end, i, d_value, child + 2);
	}
}

void print_segtree(vector<int>& seg_tree, int t_size)
{
	int num = 0, size = 1, level = 2;

	while (t_size * 2 > size)
	{
		size *= 2; // ���׸�Ʈ Ʈ���� ũ�Ⱑ ������ȭƮ�� ���°� �ǵ��� �����Ѵ�
	}

	for (int i = 1; i < size; i++)
	{
		cout << " [ " << seg_tree[i - 1] << " ] ";	

		if (i + 1 == level)
		{
			level *= 2;
			cout << '\n';
		}

	}

	
}

int main()
{
	int height = 0, t_size = 0, num = 0;
	
	t_size = construct_list(list, seg_tree, t_size);

	segtree_update(seg_tree, 0, t_size - 1, 3, 10, 0);

	cout << "�ش� ������ ���� " << query_sum(seg_tree, 0, t_size - 1, 2, 5, 0) << " �Դϴ�. " << '\n';

	print_segtree(seg_tree, t_size);

}






*/