

#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>

using namespace std;

class airplane {
private:
	int airnum = 0; // 비행기 번호 (식별자)
	int fuel = 100; // 연료
	int now_fuel = 100; // 현재 연료
	int loss_fuel = 1; // 단위 시간당 잃는 연료
	int waiting = 0; // 대기중인 시간

	bool accident = false; // 사고여부
	bool flying = false; // 비행여부
	bool need_landing = false; // 착륙 필요 여부 (연료 부족할경우 분기 발생)
	bool emergency_landing = false; // 긴급 착륙 여부
	bool useable = true; // 비행기 사용가능여부

public:
	void set_initial()
	{
		cout << "비행기의 번호를 입력하십시오 : ";
		cin >> airnum;

		cout << "비행기의 연료량을 입력하십시오 : ";
		cin >> fuel;
		now_fuel = fuel;

		cout << "단위 시간당 소모하는 연료량을 입력하십시오 : ";
		cin >> loss_fuel;
	}
	void set_loss(int input) // 단위 시간당 잃는 연료
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
		cout << "\n " << airnum << "번 : ";

		if (check_useable() == false)
			cout << "사용불가\n";

		else if (check_need_landing())
			cout << "비행중\n";

		else
			cout << "대기중\n";

		cout << " 비행 가능 시간 : " << get_limittime() << "초";

	}


	int get_limittime() // 제한시간
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
			return airnum * 10 + 1; // 이륙 (날고있음)
		else
			return airnum * 10; // 착륙 (안 날고있음)
	}
	int get_now_fuel()
	{
		return now_fuel;
	}
	int get_status()
	{
		if (check_useable()) // 사용가능여부 확인 (사고유무)
		{
			if (check_flying() && check_need_landing())
				return 1; // 비행중

			else // 이륙하지 않고 큐에 남아있는 상태
			{
				engage_fuel();
				return 0; // 대기중
				//takeoff_priority.push_back(make_pair(air_1.check_engaged_full(), air_1.get_airnum(1)));
			}
		}

		return -1; // 사용불가
	}


	bool check_emergency_landing()
	{
		return emergency_landing;
	}
	bool check_accident() // 사고여부 반환
	{
		if (get_limittime() < 0)
			return true;

		return false;
	}
	bool check_flying() // 비행 여부
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
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4) // 사고, 비상착륙 추가
{
	cout << "\n\n";

	air_1.print_status();
	air_2.print_status();
	air_3.print_status();
	air_4.print_status();

	cout << "\n\n [ 비행중 ] \n ";

	if (air_1.check_flying()) { cout << air_1.get_airnum(air_1.check_flying()); cout << "\n "; }
	if (air_2.check_flying()) { cout << air_2.get_airnum(air_2.check_flying()); cout << "\n "; }
	if (air_3.check_flying()) { cout << air_3.get_airnum(air_3.check_flying()); cout << "\n "; }
	if (air_4.check_flying()) { cout << air_4.get_airnum(air_4.check_flying()); cout << "\n "; }

	cout << "\n [ 착륙 및 대기 ] ";

	cout << "\n\n [ 1번 공항 ]\n ";

	if (airport1_landing.size() > 0)
	{
		cout << airport1_landing.front() << " ";
		if (airport1_landing.size() == 2)
			cout << airport1_landing.back() << " ";
	}

	cout << "\n\n [ 2번 공항 ]\n ";

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
	// 비행기 사용 여부 초기화 (사용할 기수 지정)

	air_1.set_initial();  // 위 요소들 initial_setting()에서 처리
	air_2.set_initial();
	air_3.set_initial();
	air_4.set_initial();

	airport1_landing.push(air_1.get_airnum(air_1.check_flying()));
	airport1_landing.push(air_2.get_airnum(air_2.check_flying()));
	airport2_landing.push(air_3.get_airnum(air_3.check_flying()));
	airport2_landing.push(air_4.get_airnum(air_4.check_flying()));

	cout << "테스트 시간 입력 :";
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
	// 어떤 비행기가 pop 된건지도 추가해야 함

	// 착륙큐에서는 먼저 들어온 비행기가 먼저 나가야 함
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

	if (airport3.size() > 0) // 이상함
	{
		if (airport3.back() == air_num)
			swap(airport3.front(), airport3.back());
		if (airport3.front() == air_num)
			airport3.pop();
	}

	// air_num 번호 따라 class airplane 초기화
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
	if (airport_num == 0) return airport_num; // 이륙불가

	else
	{
		// 비행기 상태를 비행 상태로 변경 set_flying(true);
		// 비행기 내부에 대기중인 큐에서 비행기 값 제거 (비행 시작했으므로)
		// 비행하면 단위 시간동안 해당 큐 이용불가
		airplane_initiate(air_num, airport1_used, airport2_used, airport3_used,
			airport1_takeoff, airport2_takeoff, airport3, air_1, air_2, air_3, air_4); // 이륙때만 필요


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
	if (airport_num == -1) return airport_num; // 사고
	if (airport_num == 0) return airport_num; // 착륙불가

	if (airport_num == 1) airport1_landing.push(air_num);
	if (airport_num == 2) airport2_landing.push(air_num);
	if (airport_num == 3) airport3.push(air_num); // airport3에 있는 값이 이륙인지 출력인지 확인

	update_situation(air_num, air_1, air_2, air_3, air_4);

	return airport_num;
}


int search_takeoff_airport(bool& airport1_used, bool& airport2_used, bool& airport3_used,
	queue<int>& airport1_takeoff, queue<int>& airport2_takeoff, queue<int>& airport3) // 이륙위치 반환
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
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3) // 착륙위치 반환
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

	else if (situation == 0) // - 1 = 사고 | 0 = 착륙불가
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

	if (situation % 2 == 1) // 착륙 (날고있는 상태)
		find_result = landing_airplane(search_landing_airport(situation, airport1_used, airport2_used, airport3_used,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used,
			airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4);

	else // 이륙 (대기중)
		find_result = takeoff_airplane(search_takeoff_airport(airport1_used, airport2_used, airport3_used,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used,
			airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4);

	return find_result;


}

void cal_priority(vector <pair<bool, int>>& takeoff_priority, vector <pair<int, int>>& landing_priority,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4) // 비행기의 비행 여부 및 우선순위를 판단
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

	// 수집한 벡터값으로 이/착륙 우선순위를 매긴다

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
	int test_time = 0, remain_limit_avg = 0; // 실험 시간, 남은 제한시간 평균
	int wait_takeoff = 0, wait_landing = 0; // 이륙, 착륙 대기시간
	int emergency_landing = 0, accident = 0; // 비상착륙, 사고
	int airport_decided_line = 0;

	bool airport1_used = false, airport2_used = false, airport3_used = false; // 단위 시간에 사용되었는지 여부 검사
	bool IsEmergency = false, IsTakeoff = false;

	vector <pair<bool, int>> takeoff_priority; // 이/착륙할 비행기 데이터 저장 -> sort() 함수로 정렬, 순서대로 이/착륙
	vector <pair<int, int>> landing_priority; // 이륙 : 완충여부/비행기번호, 착륙 : 비행가능시간/비행기번호

	airplane air_1;
	airplane air_2;
	airplane air_3;
	airplane air_4;

	queue<int> airport1_takeoff; queue<int> airport1_landing;
	queue<int> airport2_takeoff; queue<int> airport2_landing;
	queue<int> airport3;

	test_time = initial_setting(air_1, air_2, air_3, air_4, airport1_landing, airport2_landing, test_time);

	cout << "\n\n [ 초기 상태 ] \n\n";
	print_result(airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
		air_1, air_2, air_3, air_4); // 단위 시간마다 현재 상태 출력


	while (test_time)
	{
		// vector 이/착륙 데이터 우선저장 필요

		update_fuel(air_1, air_2, air_3, air_4);

		cal_priority(takeoff_priority, landing_priority, air_1, air_2, air_3, air_4);


		// 수집한 벡터값으로 이/착륙 우선순위를 매긴다

		sort(landing_priority.begin(), landing_priority.end());
		sort(takeoff_priority.begin(), takeoff_priority.end());

		// 우선순위대로 이/착륙을 시도한다. 우선순위는 긴급착륙 -> 이륙 -> 착륙 순으로 매긴다.


		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first == 0) // 비상착륙 상황. (수정 필요)
					find_airport(landing_priority[i].second, landing_priority[i].second, airport1_used, airport2_used, airport3_used,
						airport1_takeoff, airport1_landing, airport2_takeoff,
						airport2_landing, airport3, air_1, air_2, air_3, air_4);
		// 적절한 큐를 찾는다. 큐값을 찾지 못한다면 사고로 기록한다.
		// 활주로는 단위시간마다 한 번만 사용할 수 있음에 유의한다.

		if (takeoff_priority.size() > 0)
			for (int i = 0; i < takeoff_priority.size(); i++)
				if (takeoff_priority[i].first == true) // 이륙 상황 (현재 대기상태)
					find_airport(takeoff_priority[i].second % 2, takeoff_priority[i].second, airport1_used, airport2_used, airport3_used,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first != 0) // 착륙 상황 (현재 비행중)
					find_airport(landing_priority[i].second % 2, landing_priority[i].second, airport1_used, airport2_used, airport3_used,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		print_result(airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4); // 단위 시간마다 현재 상태 출력


		unit_setting(landing_priority, takeoff_priority, airport1_takeoff, airport1_landing,
			airport2_takeoff, airport2_landing, airport3); // 세팅 초기화 (airport_used 초기화 등). Sleep(1000)도 여기서 해결. 이륙장 초기화도 필요
		test_time--; // unit_setting()에 삽입
	}

	conclusion();
}

int main()
{
	test();


	return 0;
}