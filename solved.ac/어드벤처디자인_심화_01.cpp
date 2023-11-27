

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

	int waiting_takeoff = 0; // ��� �̷� ��� �ð�
	int waiting_landing = 0; // ��� ���� ��� �ð�
	int landing_remain_fuel = 0; // ���� �� ���� �ִ� ���� �ð��� ���

	bool accident = false; // �����
	bool flying = false; // ���࿩��
	bool emergency_landing = false; // ��� ���� ����
	bool now_landing = false; // �̹� ���� �ð������� ���� ����

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
		now_fuel += get_loss_fuel();
		if (now_fuel > fuel)
			now_fuel = fuel;
	}
	void using_fuel()
	{
		now_fuel -= loss_fuel;
	}
	void set_flying(bool flying_now)
	{
		if (flying_now == true)
		{
			flying = true;
		}
			
		else
		{
			flying = false;
		}
			
	}
	void print_status()
	{
		int airnum = get_airnum(-1);
		cout << "\n " << airnum << "�� : ";

		if (check_accident())
		{
			cout << "���\n";
			return;
		}
			

		else if (check_flying())
			cout << "������\n";

		else
			cout << "�����\n";

		cout << " ���� ���� �ð� : " << get_limittime() << "��";

	}
	void set_accident(bool check)
	{
		accident = check;
	}
	void set_now_landing(bool check)
	{
		now_landing = check;
	}


	int get_now_landing()
	{
		return now_landing;
	}
	int get_limittime() // ���ѽð�
	{
		return (now_fuel / loss_fuel);
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
	int get_loss_fuel()
	{
		return loss_fuel;
	}
	int get_status()
	{
		if (check_accident()) // ��밡�ɿ��� Ȯ�� (�������)
			return -1; // ���Ұ�

		else if (check_flying()) // check_need_landing();
			if (get_limittime() < 3)
				return 11; // �����ʿ�
			else
				return 10; // ������

		else  // �̷����� �ʰ� ť�� �����ִ� ����
		{
				engage_fuel();
				if (check_engaged_full())
					return 1; // �̷��ʿ�
				else
					return 0;
		}
		
	}


	bool check_emergency_landing()
	{
		return emergency_landing;
	}
	bool check_accident() // ����� ��ȯ
	{
		return accident;
	}
	bool check_flying() // ���� ����
	{
		return flying;
	}
	bool check_engaged_full()
	{
		if (now_fuel == fuel) return true;
		else return false;
	}
};

void print_result(int test_time, queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff,
	queue<int>& airport2_landing, queue<int>& airport3,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4, bool airport3_used_takeoff) // ���, ������� �߰�
{
	int remain_avg = 0, landing_num = 0;

	if (test_time==0) cout << "\n\n [ �ʱ� ���� ] ";
	else cout << "\n\n [ " << test_time << "�� ��� ] \n\n ";

	air_1.print_status();
	air_2.print_status();
	air_3.print_status();
	air_4.print_status();

	cout << "\n\n [ ������ ] \n ";

	if (air_1.check_flying()) { cout << air_1.get_airnum(air_1.check_flying()); cout << "\n "; }
	if (air_2.check_flying()) { cout << air_2.get_airnum(air_2.check_flying()); cout << "\n "; }
	if (air_3.check_flying()) { cout << air_3.get_airnum(air_3.check_flying()); cout << "\n "; }
	if (air_4.check_flying()) { cout << air_4.get_airnum(air_4.check_flying()); cout << "\n "; }
	
	

	cout << "\n\n [ 1�� ���� ]\n  [ �̷� ť ] : ";

	if (airport1_takeoff.size() > 0)
		cout << airport1_takeoff.front() << " ";

	cout << "\n  [ ���� ť ] : ";

	if (airport1_landing.size() > 0)
	{
		cout << airport1_landing.front() << " ";
		if (airport1_landing.size() == 2)
			cout << airport1_landing.back() << " ";
	}

	cout << "\n\n [ 2�� ���� ]\n  [ �̷� ť ] : ";

	if (airport2_takeoff.size() > 0)
		cout << airport2_takeoff.front() << " ";

	cout << "\n  [ ���� ť ] : ";

	if (airport2_landing.size() > 0)
	{
		cout << airport2_landing.front() << " ";
		if (airport2_landing.size() == 2)
			cout << airport2_landing.back() << " ";
	}

	cout << "\n\n [ 3�� ���� ] \n";

	if (airport3_used_takeoff)
		cout << "  [ �̷� ť ] : " << airport3.front();
	else if (airport3.size() > 0)
		cout << "  [ ���� ť ] : " << airport3.front();

	cout << "\n\n ���� �� ���� �ִ� ���� �ð��� ��� : ";

	if (air_1.get_now_landing())
	{
		landing_num++;
		remain_avg += air_1.get_limittime();
	}	
	if (air_2.get_now_landing()) 
	{
		landing_num++;
		remain_avg += air_2.get_limittime();
	}
	if (air_3.get_now_landing())
	{
		landing_num++;
		remain_avg += air_3.get_limittime();
	}
	if (air_4.get_now_landing())
	{
		landing_num++;
		remain_avg += air_4.get_limittime();
	}

	if (landing_num == 0) cout << " ������ ����� ���� ";
	else cout << remain_avg / (float)landing_num << " �� ";

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

	cout << "�׽�Ʈ �ð� �Է� : ";
	cin >> test_time;
	return test_time;


}

void unit_setting(vector <pair<int, int>>& landing_priority, vector <pair<bool, int>>& takeoff_priority,
	queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff, queue<int>& airport2_landing, queue<int>& airport3,
	bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	airport1_used = false;
	airport2_used = false;
	airport3_used_takeoff = false;

	landing_priority.clear();
	takeoff_priority.clear();

	air_1.set_now_landing(airport1_used);
	air_2.set_now_landing(airport1_used);
	air_3.set_now_landing(airport1_used);
	air_4.set_now_landing(airport1_used);

	// �� ���ָ� �ȵ� (�������ΰ͸�)
	

	while (!airport1_takeoff.empty())
		airport1_takeoff.pop();
	while (!airport2_takeoff.empty())
		airport2_takeoff.pop();
	while (!airport3.empty())
		if (airport3.front() % 2 == 1)
			airport3.pop();
		else
			break;
		
}

void conclusion()
{

}

void airplane_initiate(int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	// ����Ⱑ �̷����� ��, ����ť�� �ִ� ����� ���� ����
	// � ����Ⱑ pop �Ȱ����� �߰��ؾ� ��

	// ����ť������ ���� ���� ����Ⱑ ���� ������ ��
	if (airport1_landing.size() > 0)
	{
		if (airport1_landing.back() == air_num)
			swap(airport1_landing.front(), airport1_landing.back());
		if (airport1_landing.front() == air_num)
			airport1_landing.pop();
	}


	if (airport2_landing.size() > 0)
	{
		if (airport2_landing.back() == air_num)
			swap(airport2_landing.front(), airport2_landing.back());
		if (airport2_landing.front() == air_num)
			airport2_landing.pop();
	}

	if (airport3.size() > 0)
		if (airport3.front() == air_num)
			airport3.pop();

	// air_num ��ȣ ���� class airplane �ʱ�ȭ
}

void update_situation(int air_num, bool flying, airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	if (air_1.get_airnum(-1) == air_num / 10)
		if (flying)
			air_1.set_flying(flying);
		else
		{
			air_1.set_now_landing(!flying);
			air_1.set_flying(flying);
		}
			
	if (air_2.get_airnum(-1) == air_num / 10)
		if (flying)
			air_2.set_flying(flying);
		else
		{
			air_2.set_now_landing(!flying);
			air_2.set_flying(flying);
		}

	if (air_3.get_airnum(-1) == air_num / 10)
		if (flying)
			air_3.set_flying(flying);
		else
		{
			air_3.set_now_landing(!flying);
			air_3.set_flying(flying);
		}

	if (air_4.get_airnum(-1) == air_num / 10)
		if (flying)
			air_4.set_flying(flying);
		else
		{
			air_4.set_now_landing(!flying);
			air_4.set_flying(flying);
		}
	
}

int takeoff_airplane(int airport_num, int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
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

		if (airport_num == 1 && airport1_used == false)
		{
			airport1_takeoff.push(air_num + 1);
			airport1_used = true;
			airplane_initiate(air_num, airport1_used, airport2_used, airport3_used_takeoff,
				airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4); // �̷����� �ʿ�

			update_situation(air_num, true, air_1, air_2, air_3, air_4);
		}

		if (airport_num == 2 && airport2_used == false)
		{
			airport2_takeoff.push(air_num + 1);
			airport2_used = true;
			airplane_initiate(air_num, airport1_used, airport2_used, airport3_used_takeoff,
				airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4); // �̷����� �ʿ�

			update_situation(air_num, true, air_1, air_2, air_3, air_4);
		}

		if (airport_num == 3 && airport3_used_takeoff == false)
		{
			airport3.push(air_num + 1);
			airport3_used_takeoff = true;
			airplane_initiate(air_num, airport1_used, airport2_used, airport3_used_takeoff,
				airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4); // �̷����� �ʿ�

			update_situation(air_num, true, air_1, air_2, air_3, air_4);
		};
		
	}

	return airport_num;
}

int landing_airplane(int airport_num, int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	if (airport_num == -1) // ���
		return airport_num;

	if (airport_num == 0) // �����Ұ�
	{
		if (air_1.get_airnum(-1) == air_num / 10 && air_1.get_limittime() <= 0)
		{
			air_1.set_accident(true);
			update_situation(air_num, false, air_1, air_2, air_3, air_4);
		}			
		if (air_2.get_airnum(-1) == air_num / 10 && air_2.get_limittime() <= 0)
		{
			air_2.set_accident(true);
			update_situation(air_num, false, air_1, air_2, air_3, air_4);
		}
		if (air_3.get_airnum(-1) == air_num / 10 && air_3.get_limittime() <= 0)
		{
			air_3.set_accident(true);
			update_situation(air_num, false, air_1, air_2, air_3, air_4);
		}
		if (air_4.get_airnum(-1) == air_num / 10 && air_4.get_limittime() <= 0)
		{
			air_4.set_accident(true);
			update_situation(air_num, false, air_1, air_2, air_3, air_4);
		}

		

		return airport_num;
	}

	if (airport_num == 1 && airport1_used == false)
	{
		airport1_landing.push(air_num - 1);
		airport1_used = true;

		update_situation(air_num, false, air_1, air_2, air_3, air_4);
	}

	if (airport_num == 2 && airport2_used == false)
	{
		airport2_landing.push(air_num - 1);
		airport2_used = true;

		update_situation(air_num, false, air_1, air_2, air_3, air_4);
	}
				
	if (airport_num == 3 && airport3.size() == 0)
	{
		airport3.push(air_num - 1); // airport3�� �ִ� ���� �̷����� ������� Ȯ�� + airport3�� �� ������ '��� ����' �����ϴ��� Ȯ��

		update_situation(air_num, false, air_1, air_2, air_3, air_4);
	}
		
	return airport_num;
}


int search_takeoff_airport(int air_num, queue<int>& airport1_landing, queue<int>& airport2_landing, 
	queue<int>& airport3) // �̷���ġ ��ȯ
{
	// ������ ������ �������� �̷� �����ϵ��� ����

	if (airport1_landing.size() > 0)
		if (airport1_landing.front() == air_num || airport1_landing.back() == air_num)
			return 1;
	if (airport2_landing.size() > 0)
		if (airport2_landing.front() == air_num || airport2_landing.back() == air_num)
			return 2;
	if (airport3.size() > 0)
		if (airport3.front() == air_num || airport3.back() == air_num)
			return 3;

	else
		return 0;
}

int search_landing_airport(int situation, bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3) // ������ġ ��ȯ
{
	if (airport1_used == false && airport1_landing.size() == 0)
		return 1;
	else if (airport2_used == false && airport2_landing.size() == 0)
		return 2;

	else if (airport1_used == false && airport1_landing.size() < 2)
		return 1;
	else if (airport2_used == false && airport2_landing.size() < 2)
		return 2;

	else if (airport3_used_takeoff == false && airport3.size() == 0) // ���� �ʿ� (��� ������ ����)
		return 3;

	else if (situation < 0) // -1 = ���
		return -1;

	else
		return 0; // �����Ұ�

}


int find_airport(int situation, int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
	queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff,
	queue<int>& airport2_landing, queue<int>& airport3, airplane& air_1, airplane& air_2, airplane& air_3,
	airplane& air_4)
{
	int find_result = 0;

	if (air_num % 2 == 1) // ���� (�����ִ� ����)
		find_result = landing_airplane(search_landing_airport(situation, airport1_used, airport2_used, airport3_used_takeoff,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used_takeoff,
			airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4);

	else // �̷� (�����)
		find_result = takeoff_airplane(search_takeoff_airport(air_num,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used_takeoff,
			airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4);

	return find_result;

	// 0 -> ���, -1 -> ���� �Ұ�
}

void cal_priority(vector <pair<bool, int>>& takeoff_priority, vector <pair<int, int>>& landing_priority,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4) // ������� ���� ���� �� �켱������ �Ǵ�
{
	if (air_1.get_status() == 11)
		landing_priority.push_back(make_pair(air_1.get_limittime(), air_1.get_airnum(air_1.check_flying())));
	else if (air_1.get_status() == 1)
		takeoff_priority.push_back(make_pair(air_1.check_engaged_full(), air_1.get_airnum(air_1.check_flying())));

	if (air_2.get_status() == 11)
		landing_priority.push_back(make_pair(air_2.get_limittime(), air_2.get_airnum(air_2.check_flying())));
	else if (air_2.get_status() == 1)
		takeoff_priority.push_back(make_pair(air_2.check_engaged_full(), air_2.get_airnum(air_2.check_flying())));

	if (air_3.get_status() == 11)
		landing_priority.push_back(make_pair(air_3.get_limittime(), air_3.get_airnum(air_3.check_flying())));
	else if (air_3.get_status() == 1)
		takeoff_priority.push_back(make_pair(air_3.check_engaged_full(), air_3.get_airnum(air_3.check_flying())));

	if (air_4.get_status() == 11)
		landing_priority.push_back(make_pair(air_4.get_limittime(), air_4.get_airnum(air_4.check_flying())));
	else if (air_4.get_status() == 1)
		takeoff_priority.push_back(make_pair(air_4.check_engaged_full(), air_4.get_airnum(air_4.check_flying())));

	// ������ ���Ͱ����� ��/���� �켱������ �ű��

	sort(landing_priority.begin(), landing_priority.end());
	sort(takeoff_priority.begin(), takeoff_priority.end());

}

void update_fuel(airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	if (air_1.check_flying()) air_1.using_fuel();
	else air_1.engage_fuel();

	if (air_2.check_flying()) air_2.using_fuel();
	else air_2.engage_fuel();

	if (air_3.check_flying()) air_3.using_fuel();
	else air_3.engage_fuel();

	if (air_4.check_flying()) air_4.using_fuel();
	else air_4.engage_fuel();
}

void test()
{
	int test_time = 0, initial_time = 0; // ���� �ð�, ���� �ð�
	int wait_takeoff = 0, wait_landing = 0; // �̷�, ���� ���ð�
	int emergency_landing = 0, accident = 0; // �������, ���
	int airport_decided_line = 0;

	bool airport1_used = false, airport2_used = false, airport3_used_takeoff = false; // ���� �ð��� ���Ǿ����� ���� �˻�

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
	initial_time = test_time;

	print_result(initial_time - test_time, airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
		air_1, air_2, air_3, air_4, airport3_used_takeoff); // ���� �ð����� ���� ���� ���


	while (test_time)
	{
		// vector ��/���� ������ �켱���� �ʿ�

		update_fuel(air_1, air_2, air_3, air_4);

		cal_priority(takeoff_priority, landing_priority, air_1, air_2, air_3, air_4);

		sort(landing_priority.begin(), landing_priority.end());
		sort(takeoff_priority.begin(), takeoff_priority.end());

		// �켱������� ��/������ �õ��Ѵ�. �켱������ ������� -> �̷� -> ���� ������ �ű��.


		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first <= 0) // ������� ��Ȳ. (���� �ʿ�)
					find_airport(landing_priority[i].first, landing_priority[i].second, airport1_used, airport2_used, airport3_used_takeoff,
						airport1_takeoff, airport1_landing, airport2_takeoff,
						airport2_landing, airport3, air_1, air_2, air_3, air_4);
		// ������ ť�� ã�´�. ť���� ã�� ���Ѵٸ� ���� ����Ѵ�.
		// Ȱ�ַδ� �����ð����� �� ���� ����� �� ������ �����Ѵ�.

		if (takeoff_priority.size() > 0)
			for (int i = 0; i < takeoff_priority.size(); i++)
				if (takeoff_priority[i].first == true) // �̷� ��Ȳ (���� ������)
					find_airport(takeoff_priority[i].second % 2, takeoff_priority[i].second, airport1_used, airport2_used, airport3_used_takeoff,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first != 0) // ���� ��Ȳ (���� ������)
					find_airport(landing_priority[i].first, landing_priority[i].second, airport1_used, airport2_used, airport3_used_takeoff,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		print_result(initial_time - test_time + 1, airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4, airport3_used_takeoff); // ���� �ð����� ���� ���� ���


		unit_setting(landing_priority, takeoff_priority, airport1_takeoff, airport1_landing,
			airport2_takeoff, airport2_landing, airport3, airport1_used, airport2_used, airport3_used_takeoff,
			air_1, air_2, air_3, air_4); 
		// ���� �ʱ�ȭ (airport_used �ʱ�ȭ ��). Sleep(1000)�� ���⼭ �ذ�. �̷��� �ʱ�ȭ�� �ʿ�
		test_time--;
	}

	conclusion();
}

int main()
{
	test();

	return 0;
}