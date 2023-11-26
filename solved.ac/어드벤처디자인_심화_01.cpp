

#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>

using namespace std;

class airplane {
private:
	int airnum = 0; // ����� ��ȣ (�ĺ���)
	int fuel = 100; // ����
	int now_fuel = 100; // ���� ����
	int loss_fuel = 1; // ���� �ð��� �Ҵ� ����
	int waiting = 0; // ������� �ð�

	bool accident = false; // �����
	bool flying = false; // ���࿩��
	bool need_landing = false; // ���� �ʿ� ���� (���� �����Ұ�� �б� �߻�)
	bool emergency_landing = false; // ��� ���� ����
	bool useable = true; // ����� ��밡�ɿ���

public:
	void set_initial()
	{
		cout << "������� ��ȣ�� �Է��Ͻʽÿ� : ";
		cin >> airnum;

		cout << "������� ���ᷮ�� �Է��Ͻʽÿ� : ";
		cin >> fuel;
		now_fuel = fuel;

		cout << "���� �ð��� �Ҹ��ϴ� ���ᷮ�� �Է��Ͻʽÿ� : ";
		cin >> loss_fuel;
	}
	void set_loss(int input) // ���� �ð��� �Ҵ� ����
	{
		loss_fuel = input;
	}
	void engage_fuel()
	{
		now_fuel += fuel / 10;
		if (now_fuel > fuel)
			now_fuel = fuel;
	}
	void using_fuel()
	{
		now_fuel -= loss_fuel;
	}
	void set_need_landing()
	{
		need_landing = true;
	}
	void set_flying(bool flying_now)
	{
		if (flying_now == true)
			flying = true;
		else
			flying = false;
	}
	void print_status()
	{
		int airnum = get_airnum(-1);
		cout << "\n " << airnum << "�� : ";

		if (check_useable() == false)
			cout << "���Ұ�\n";

		else if (check_need_landing())
			cout << "������\n";

		else
			cout << "�����\n";

		cout << " ���� ���� �ð� : " << get_limittime() << "��";

	}


	int get_limittime() // ���ѽð�
	{
		return (now_fuel / loss_fuel);
	}
	int get_waiting()
	{
		return waiting;
	}
	int get_airnum(int value)
	{
		if (value == -1)
			return airnum;
		if (value == 1)
			return airnum * 10 + 1; // �̷� (��������)
		else
			return airnum * 10; // ���� (�� ��������)
	}
	int get_now_fuel()
	{
		return now_fuel;
	}
	int get_status()
	{
		if (check_useable()) // ��밡�ɿ��� Ȯ�� (�������)
		{
			if (check_flying() && check_need_landing())
				return 1; // ������

			else // �̷����� �ʰ� ť�� �����ִ� ����
			{
				engage_fuel();
				return 0; // �����
				//takeoff_priority.push_back(make_pair(air_1.check_engaged_full(), air_1.get_airnum(1)));
			}
		}

		return -1; // ���Ұ�
	}


	bool check_emergency_landing()
	{
		return emergency_landing;
	}
	bool check_accident() // ����� ��ȯ
	{
		if (get_limittime() < 0)
			return true;

		return false;
	}
	bool check_flying() // ���� ����
	{
		return flying;
	}
	bool check_need_landing()
	{
		return need_landing;
	}
	bool check_useable()
	{
		return useable;
	}
	bool check_engaged_full()
	{
		if (now_fuel == fuel) return true;
		else return false;
	}
};

void print_result(queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff,
	queue<int>& airport2_landing, queue<int>& airport3,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4) // ���, ������� �߰�
{
	cout << "\n\n";

	air_1.print_status();
	air_2.print_status();
	air_3.print_status();
	air_4.print_status();

	cout << "\n\n [ ������ ] \n ";

	if (air_1.check_flying()) { cout << air_1.get_airnum(air_1.check_flying()); cout << "\n "; }
	if (air_2.check_flying()) { cout << air_2.get_airnum(air_2.check_flying()); cout << "\n "; }
	if (air_3.check_flying()) { cout << air_3.get_airnum(air_3.check_flying()); cout << "\n "; }
	if (air_4.check_flying()) { cout << air_4.get_airnum(air_4.check_flying()); cout << "\n "; }

	cout << "\n [ ���� �� ��� ] ";

	cout << "\n\n [ 1�� ���� ]\n ";

	if (airport1_landing.size() > 0)
	{
		cout << airport1_landing.front() << " ";
		if (airport1_landing.size() == 2)
			cout << airport1_landing.back() << " ";
	}

	cout << "\n\n [ 2�� ���� ]\n ";

	if (airport2_landing.size() > 0)
	{
		cout << airport2_landing.front() << " ";
		if (airport2_landing.size() == 2)
			cout << airport2_landing.back() << " ";
	}



	cout << "\n\n ---------------------------------------------------------------------------";

	Sleep(1000);
}

int initial_setting(airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4,
	queue<int>& airport1_landing, queue<int>& airport2_landing, int test_time)
{
	// ����� ��� ���� �ʱ�ȭ (����� ��� ����)

	air_1.set_initial();  // �� ��ҵ� initial_setting()���� ó��
	air_2.set_initial();
	air_3.set_initial();
	air_4.set_initial();

	airport1_landing.push(air_1.get_airnum(air_1.check_flying()));
	airport1_landing.push(air_2.get_airnum(air_2.check_flying()));
	airport2_landing.push(air_3.get_airnum(air_3.check_flying()));
	airport2_landing.push(air_4.get_airnum(air_4.check_flying()));

	cout << "�׽�Ʈ �ð� �Է� :";
	cin >> test_time;
	return test_time;


}

void unit_setting(vector <pair<int, int>>& landing_priority, vector <pair<bool, int>>& takeoff_priority,
	queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff, queue<int>& airport2_landing, queue<int>& airport3)
{
	
	landing_priority.clear();
	takeoff_priority.clear();

	while (!airport1_takeoff.empty())
		airport1_takeoff.pop();
	while (!airport1_landing.empty())
		airport1_landing.pop();
	while (!airport2_takeoff.empty())
		airport2_takeoff.pop();
	while (!airport2_landing.empty())
		airport2_landing.pop();
	while (!airport3.empty())
		airport3.pop();

}

void conclusion()
{

}

void airplane_initiate(int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used,
	queue<int>& airport1_takeoff, queue<int>& airport2_takeoff, queue<int>& airport3,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	// � ����Ⱑ pop �Ȱ����� �߰��ؾ� ��

	// ����ť������ ���� ���� ����Ⱑ ���� ������ ��
	if (airport1_takeoff.size() > 0)
	{
		if (airport1_takeoff.back() == air_num)
			swap(airport1_takeoff.front(), airport1_takeoff.back());
		if (airport1_takeoff.front() == air_num)
			airport1_takeoff.pop();
	}


	if (airport2_takeoff.size() > 0)
	{
		if (airport2_takeoff.back() == air_num)
			swap(airport2_takeoff.front(), airport2_takeoff.back());
		if (airport2_takeoff.front() == air_num)
			airport2_takeoff.pop();
	}

	if (airport3.size() > 0) // �̻���
	{
		if (airport3.back() == air_num)
			swap(airport3.front(), airport3.back());
		if (airport3.front() == air_num)
			airport3.pop();
	}

	// air_num ��ȣ ���� class airplane �ʱ�ȭ
}

void update_situation(int air_num, airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	if (air_1.get_airnum(0) == air_num)
		air_1.set_flying(true);
	if (air_1.get_airnum(1) == air_num)
		air_1.set_flying(false);

	if (air_2.get_airnum(0) == air_num)
		air_2.set_flying(true);
	if (air_2.get_airnum(1) == air_num)
		air_2.set_flying(false);

	if (air_3.get_airnum(0) == air_num)
		air_3.set_flying(true);
	if (air_3.get_airnum(1) == air_num)
		air_3.set_flying(false);

	if (air_4.get_airnum(0) == air_num)
		air_4.set_flying(true);
	if (air_4.get_airnum(1) == air_num)
		air_4.set_flying(false);
	
}

int takeoff_airplane(int airport_num, int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used,
	queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff,
	queue<int>& airport2_landing, queue<int>& airport3, airplane& air_1, airplane& air_2, airplane& air_3,
	airplane& air_4)
{
	if (airport_num == 0) return airport_num; // �̷��Ұ�

	else
	{
		// ����� ���¸� ���� ���·� ���� set_flying(true);
		// ����� ���ο� ������� ť���� ����� �� ���� (���� ���������Ƿ�)
		// �����ϸ� ���� �ð����� �ش� ť �̿�Ұ�
		airplane_initiate(air_num, airport1_used, airport2_used, airport3_used,
			airport1_takeoff, airport2_takeoff, airport3, air_1, air_2, air_3, air_4); // �̷����� �ʿ�


		if (airport_num == 1)
		{
			airport1_takeoff.push(air_num);
			airport1_used = true;
		}

		if (airport_num == 2)
		{
			airport2_takeoff.push(air_num);
			airport2_used = true;
		}

		if (airport_num == 3)
		{
			airport3.push(air_num);
			airport3_used = true;
		}
	}

	update_situation(air_num, air_1, air_2, air_3, air_4);

	return airport_num;
}

int landing_airplane(int airport_num, int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used,
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	if (airport_num == -1) return airport_num; // ���
	if (airport_num == 0) return airport_num; // �����Ұ�

	if (airport_num == 1) airport1_landing.push(air_num);
	if (airport_num == 2) airport2_landing.push(air_num);
	if (airport_num == 3) airport3.push(air_num); // airport3�� �ִ� ���� �̷����� ������� Ȯ��

	update_situation(air_num, air_1, air_2, air_3, air_4);

	return airport_num;
}


int search_takeoff_airport(bool& airport1_used, bool& airport2_used, bool& airport3_used,
	queue<int>& airport1_takeoff, queue<int>& airport2_takeoff, queue<int>& airport3) // �̷���ġ ��ȯ
{
	if (airport3_used == false && airport3.size() == 1)
		return 3;
	else if (airport1_used == false && airport1_takeoff.size() == 2)
		return 1;
	else if (airport2_used == false && airport2_takeoff.size() == 2)
		return 2;

	else
		return 0;
}

int search_landing_airport(int situation, bool& airport1_used, bool& airport2_used, bool& airport3_used,
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3) // ������ġ ��ȯ
{
	if (airport1_used == false && airport1_landing.size() == 0)
		return 1;
	else if (airport2_used == false && airport2_landing.size() == 0)
		return 2;

	else if (airport1_used == false && airport2_used == true && airport1_landing.size() < 2)
		return 1;
	else if (airport2_used == false && airport1_used == true && airport2_landing.size() < 2)
		return 2;

	else if (airport3_used == false && airport3.size() == 0)
		return 3;

	else if (situation == 0) // - 1 = ��� | 0 = �����Ұ�
		return -1;
	else
		return 0;
}


int find_airport(int situation, int air_num, bool airport1_used, bool airport2_used, bool airport3_used,
	queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff,
	queue<int>& airport2_landing, queue<int>& airport3, airplane& air_1, airplane& air_2, airplane& air_3,
	airplane& air_4)
{
	int find_result = 0;

	if (situation % 2 == 1) // ���� (�����ִ� ����)
		find_result = landing_airplane(search_landing_airport(situation, airport1_used, airport2_used, airport3_used,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used,
			airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4);

	else // �̷� (�����)
		find_result = takeoff_airplane(search_takeoff_airport(airport1_used, airport2_used, airport3_used,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used,
			airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4);

	return find_result;


}

void cal_priority(vector <pair<bool, int>>& takeoff_priority, vector <pair<int, int>>& landing_priority,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4) // ������� ���� ���� �� �켱������ �Ǵ�
{
	if (air_1.get_status() == 0)
		takeoff_priority.push_back(make_pair(air_1.check_engaged_full(), air_1.get_airnum(air_1.check_flying())));
	else if (air_1.get_status() == 1)
		landing_priority.push_back(make_pair(air_1.get_limittime(), air_1.get_airnum(air_1.check_flying())));

	if (air_2.get_status() == 0)
		takeoff_priority.push_back(make_pair(air_2.check_engaged_full(), air_2.get_airnum(air_2.check_flying())));
	else if (air_2.get_status() == 1)
		landing_priority.push_back(make_pair(air_2.get_limittime(), air_2.get_airnum(air_2.check_flying())));

	if (air_3.get_status() == 0)
		takeoff_priority.push_back(make_pair(air_3.check_engaged_full(), air_3.get_airnum(air_3.check_flying())));
	else if (air_3.get_status() == 1)
		landing_priority.push_back(make_pair(air_3.get_limittime(), air_3.get_airnum(air_3.check_flying())));

	if (air_4.get_status() == 0)
		takeoff_priority.push_back(make_pair(air_4.check_engaged_full(), air_4.get_airnum(air_4.check_flying())));
	else if (air_4.get_status() == 1)
		landing_priority.push_back(make_pair(air_4.get_limittime(), air_4.get_airnum(air_4.check_flying())));

	// ������ ���Ͱ����� ��/���� �켱������ �ű��

	sort(landing_priority.begin(), landing_priority.end());
	sort(takeoff_priority.begin(), takeoff_priority.end());

}

void update_fuel(airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	if (air_1.check_flying() == true) air_1.using_fuel();
	else air_1.engage_fuel();

	if (air_2.check_flying() == true) air_2.using_fuel();
	else air_2.engage_fuel();

	if (air_3.check_flying() == true) air_3.using_fuel();
	else air_3.engage_fuel();

	if (air_4.check_flying() == true) air_4.using_fuel();
	else air_4.engage_fuel();
}

void test()
{
	int test_time = 0, remain_limit_avg = 0; // ���� �ð�, ���� ���ѽð� ���
	int wait_takeoff = 0, wait_landing = 0; // �̷�, ���� ���ð�
	int emergency_landing = 0, accident = 0; // �������, ���
	int airport_decided_line = 0;

	bool airport1_used = false, airport2_used = false, airport3_used = false; // ���� �ð��� ���Ǿ����� ���� �˻�
	bool IsEmergency = false, IsTakeoff = false;

	vector <pair<bool, int>> takeoff_priority; // ��/������ ����� ������ ���� -> sort() �Լ��� ����, ������� ��/����
	vector <pair<int, int>> landing_priority; // �̷� : ���濩��/������ȣ, ���� : ���డ�ɽð�/������ȣ

	airplane air_1;
	airplane air_2;
	airplane air_3;
	airplane air_4;

	queue<int> airport1_takeoff; queue<int> airport1_landing;
	queue<int> airport2_takeoff; queue<int> airport2_landing;
	queue<int> airport3;

	test_time = initial_setting(air_1, air_2, air_3, air_4, airport1_landing, airport2_landing, test_time);

	cout << "\n\n [ �ʱ� ���� ] \n\n";
	print_result(airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
		air_1, air_2, air_3, air_4); // ���� �ð����� ���� ���� ���


	while (test_time)
	{
		// vector ��/���� ������ �켱���� �ʿ�

		update_fuel(air_1, air_2, air_3, air_4);

		cal_priority(takeoff_priority, landing_priority, air_1, air_2, air_3, air_4);


		// ������ ���Ͱ����� ��/���� �켱������ �ű��

		sort(landing_priority.begin(), landing_priority.end());
		sort(takeoff_priority.begin(), takeoff_priority.end());

		// �켱������� ��/������ �õ��Ѵ�. �켱������ ������� -> �̷� -> ���� ������ �ű��.


		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first == 0) // ������� ��Ȳ. (���� �ʿ�)
					find_airport(landing_priority[i].second, landing_priority[i].second, airport1_used, airport2_used, airport3_used,
						airport1_takeoff, airport1_landing, airport2_takeoff,
						airport2_landing, airport3, air_1, air_2, air_3, air_4);
		// ������ ť�� ã�´�. ť���� ã�� ���Ѵٸ� ���� ����Ѵ�.
		// Ȱ�ַδ� �����ð����� �� ���� ����� �� ������ �����Ѵ�.

		if (takeoff_priority.size() > 0)
			for (int i = 0; i < takeoff_priority.size(); i++)
				if (takeoff_priority[i].first == true) // �̷� ��Ȳ (���� ������)
					find_airport(takeoff_priority[i].second % 2, takeoff_priority[i].second, airport1_used, airport2_used, airport3_used,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first != 0) // ���� ��Ȳ (���� ������)
					find_airport(landing_priority[i].second % 2, landing_priority[i].second, airport1_used, airport2_used, airport3_used,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		print_result(airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4); // ���� �ð����� ���� ���� ���


		unit_setting(landing_priority, takeoff_priority, airport1_takeoff, airport1_landing,
			airport2_takeoff, airport2_landing, airport3); // ���� �ʱ�ȭ (airport_used �ʱ�ȭ ��). Sleep(1000)�� ���⼭ �ذ�. �̷��� �ʱ�ȭ�� �ʿ�
		test_time--; // unit_setting()�� ����
	}

	conclusion();
}

int main()
{
	test();


	return 0;
}