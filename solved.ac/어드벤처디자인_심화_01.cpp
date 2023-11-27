

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

	int waiting_takeoff = 0; // 평균 이륙 대기 시간
	int waiting_landing = 0; // 평균 착륙 대기 시간
	int landing_remain_fuel = 0; // 착륙 시 남아 있는 제한 시간의 평균

	bool accident = false; // 사고여부
	bool flying = false; // 비행여부
	bool emergency_landing = false; // 긴급 착륙 여부
	bool now_landing = false; // 이번 단위 시간에서의 착륙 여부

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
		cout << "\n " << airnum << "번 : ";

		if (check_accident())
		{
			cout << "사고\n";
			return;
		}
			

		else if (check_flying())
			cout << "비행중\n";

		else
			cout << "대기중\n";

		cout << " 비행 가능 시간 : " << get_limittime() << "초";

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
	int get_limittime() // 제한시간
	{
		return (now_fuel / loss_fuel);
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
	int get_loss_fuel()
	{
		return loss_fuel;
	}
	int get_status()
	{
		if (check_accident()) // 사용가능여부 확인 (사고유무)
			return -1; // 사용불가

		else if (check_flying()) // check_need_landing();
			if (get_limittime() < 3)
				return 11; // 착륙필요
			else
				return 10; // 비행중

		else  // 이륙하지 않고 큐에 남아있는 상태
		{
				engage_fuel();
				if (check_engaged_full())
					return 1; // 이륙필요
				else
					return 0;
		}
		
	}


	bool check_emergency_landing()
	{
		return emergency_landing;
	}
	bool check_accident() // 사고여부 반환
	{
		return accident;
	}
	bool check_flying() // 비행 여부
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
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4, bool airport3_used_takeoff) // 사고, 비상착륙 추가
{
	int remain_avg = 0, landing_num = 0;

	if (test_time==0) cout << "\n\n [ 초기 상태 ] ";
	else cout << "\n\n [ " << test_time << "초 경과 ] \n\n ";

	air_1.print_status();
	air_2.print_status();
	air_3.print_status();
	air_4.print_status();

	cout << "\n\n [ 비행중 ] \n ";

	if (air_1.check_flying()) { cout << air_1.get_airnum(air_1.check_flying()); cout << "\n "; }
	if (air_2.check_flying()) { cout << air_2.get_airnum(air_2.check_flying()); cout << "\n "; }
	if (air_3.check_flying()) { cout << air_3.get_airnum(air_3.check_flying()); cout << "\n "; }
	if (air_4.check_flying()) { cout << air_4.get_airnum(air_4.check_flying()); cout << "\n "; }
	
	

	cout << "\n\n [ 1번 공항 ]\n  [ 이륙 큐 ] : ";

	if (airport1_takeoff.size() > 0)
		cout << airport1_takeoff.front() << " ";

	cout << "\n  [ 착륙 큐 ] : ";

	if (airport1_landing.size() > 0)
	{
		cout << airport1_landing.front() << " ";
		if (airport1_landing.size() == 2)
			cout << airport1_landing.back() << " ";
	}

	cout << "\n\n [ 2번 공항 ]\n  [ 이륙 큐 ] : ";

	if (airport2_takeoff.size() > 0)
		cout << airport2_takeoff.front() << " ";

	cout << "\n  [ 착륙 큐 ] : ";

	if (airport2_landing.size() > 0)
	{
		cout << airport2_landing.front() << " ";
		if (airport2_landing.size() == 2)
			cout << airport2_landing.back() << " ";
	}

	cout << "\n\n [ 3번 공항 ] \n";

	if (airport3_used_takeoff)
		cout << "  [ 이륙 큐 ] : " << airport3.front();
	else if (airport3.size() > 0)
		cout << "  [ 착륙 큐 ] : " << airport3.front();

	cout << "\n\n 착륙 시 남아 있는 제한 시간의 평균 : ";

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

	if (landing_num == 0) cout << " 착륙한 비행기 없음 ";
	else cout << remain_avg / (float)landing_num << " 초 ";

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

	cout << "테스트 시간 입력 : ";
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

	// 다 없애면 안됨 (비행중인것만)
	

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
	// 비행기가 이륙했을 때, 착륙큐에 있던 비행기 값을 제거
	// 어떤 비행기가 pop 된건지도 추가해야 함

	// 착륙큐에서는 먼저 들어온 비행기가 먼저 나가야 함
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

	// air_num 번호 따라 class airplane 초기화
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
	if (airport_num == 0) return airport_num; // 이륙불가

	else
	{
		// 비행기 상태를 비행 상태로 변경 set_flying(true);
		// 비행기 내부에 대기중인 큐에서 비행기 값 제거 (비행 시작했으므로)
		// 비행하면 단위 시간동안 해당 큐 이용불가

		if (airport_num == 1 && airport1_used == false)
		{
			airport1_takeoff.push(air_num + 1);
			airport1_used = true;
			airplane_initiate(air_num, airport1_used, airport2_used, airport3_used_takeoff,
				airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4); // 이륙때만 필요

			update_situation(air_num, true, air_1, air_2, air_3, air_4);
		}

		if (airport_num == 2 && airport2_used == false)
		{
			airport2_takeoff.push(air_num + 1);
			airport2_used = true;
			airplane_initiate(air_num, airport1_used, airport2_used, airport3_used_takeoff,
				airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4); // 이륙때만 필요

			update_situation(air_num, true, air_1, air_2, air_3, air_4);
		}

		if (airport_num == 3 && airport3_used_takeoff == false)
		{
			airport3.push(air_num + 1);
			airport3_used_takeoff = true;
			airplane_initiate(air_num, airport1_used, airport2_used, airport3_used_takeoff,
				airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4); // 이륙때만 필요

			update_situation(air_num, true, air_1, air_2, air_3, air_4);
		};
		
	}

	return airport_num;
}

int landing_airplane(int airport_num, int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4)
{
	if (airport_num == -1) // 사고
		return airport_num;

	if (airport_num == 0) // 착륙불가
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
		airport3.push(air_num - 1); // airport3에 있는 값이 이륙인지 출력인지 확인 + airport3에 들어갈 조건인 '비상 착륙' 만족하는지 확인

		update_situation(air_num, false, air_1, air_2, air_3, air_4);
	}
		
	return airport_num;
}


int search_takeoff_airport(int air_num, queue<int>& airport1_landing, queue<int>& airport2_landing, 
	queue<int>& airport3) // 이륙위치 반환
{
	// 비행기는 착륙한 곳에서만 이륙 가능하도록 설계

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
	queue<int>& airport1_landing, queue<int>& airport2_landing, queue<int>& airport3) // 착륙위치 반환
{
	if (airport1_used == false && airport1_landing.size() == 0)
		return 1;
	else if (airport2_used == false && airport2_landing.size() == 0)
		return 2;

	else if (airport1_used == false && airport1_landing.size() < 2)
		return 1;
	else if (airport2_used == false && airport2_landing.size() < 2)
		return 2;

	else if (airport3_used_takeoff == false && airport3.size() == 0) // 수정 필요 (비상 착륙만 가능)
		return 3;

	else if (situation < 0) // -1 = 사고
		return -1;

	else
		return 0; // 착륙불가

}


int find_airport(int situation, int air_num, bool& airport1_used, bool& airport2_used, bool& airport3_used_takeoff,
	queue<int>& airport1_takeoff, queue<int>& airport1_landing, queue<int>& airport2_takeoff,
	queue<int>& airport2_landing, queue<int>& airport3, airplane& air_1, airplane& air_2, airplane& air_3,
	airplane& air_4)
{
	int find_result = 0;

	if (air_num % 2 == 1) // 착륙 (날고있는 상태)
		find_result = landing_airplane(search_landing_airport(situation, airport1_used, airport2_used, airport3_used_takeoff,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used_takeoff,
			airport1_landing, airport2_landing, airport3, air_1, air_2, air_3, air_4);

	else // 이륙 (대기중)
		find_result = takeoff_airplane(search_takeoff_airport(air_num,
			airport1_landing, airport2_landing, airport3), air_num, airport1_used, airport2_used, airport3_used_takeoff,
			airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4);

	return find_result;

	// 0 -> 사고, -1 -> 착륙 불가
}

void cal_priority(vector <pair<bool, int>>& takeoff_priority, vector <pair<int, int>>& landing_priority,
	airplane& air_1, airplane& air_2, airplane& air_3, airplane& air_4) // 비행기의 비행 여부 및 우선순위를 판단
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

	// 수집한 벡터값으로 이/착륙 우선순위를 매긴다

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
	int test_time = 0, initial_time = 0; // 실험 시간, 최초 시간
	int wait_takeoff = 0, wait_landing = 0; // 이륙, 착륙 대기시간
	int emergency_landing = 0, accident = 0; // 비상착륙, 사고
	int airport_decided_line = 0;

	bool airport1_used = false, airport2_used = false, airport3_used_takeoff = false; // 단위 시간에 사용되었는지 여부 검사

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
	initial_time = test_time;

	print_result(initial_time - test_time, airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
		air_1, air_2, air_3, air_4, airport3_used_takeoff); // 단위 시간마다 현재 상태 출력


	while (test_time)
	{
		// vector 이/착륙 데이터 우선저장 필요

		update_fuel(air_1, air_2, air_3, air_4);

		cal_priority(takeoff_priority, landing_priority, air_1, air_2, air_3, air_4);

		sort(landing_priority.begin(), landing_priority.end());
		sort(takeoff_priority.begin(), takeoff_priority.end());

		// 우선순위대로 이/착륙을 시도한다. 우선순위는 긴급착륙 -> 이륙 -> 착륙 순으로 매긴다.


		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first <= 0) // 비상착륙 상황. (수정 필요)
					find_airport(landing_priority[i].first, landing_priority[i].second, airport1_used, airport2_used, airport3_used_takeoff,
						airport1_takeoff, airport1_landing, airport2_takeoff,
						airport2_landing, airport3, air_1, air_2, air_3, air_4);
		// 적절한 큐를 찾는다. 큐값을 찾지 못한다면 사고로 기록한다.
		// 활주로는 단위시간마다 한 번만 사용할 수 있음에 유의한다.

		if (takeoff_priority.size() > 0)
			for (int i = 0; i < takeoff_priority.size(); i++)
				if (takeoff_priority[i].first == true) // 이륙 상황 (현재 대기상태)
					find_airport(takeoff_priority[i].second % 2, takeoff_priority[i].second, airport1_used, airport2_used, airport3_used_takeoff,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		if (landing_priority.size() > 0)
			for (int i = 0; i < landing_priority.size(); i++)
				if (landing_priority[i].first != 0) // 착륙 상황 (현재 비행중)
					find_airport(landing_priority[i].first, landing_priority[i].second, airport1_used, airport2_used, airport3_used_takeoff,
						airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
						air_1, air_2, air_3, air_4);

		print_result(initial_time - test_time + 1, airport1_takeoff, airport1_landing, airport2_takeoff, airport2_landing, airport3,
			air_1, air_2, air_3, air_4, airport3_used_takeoff); // 단위 시간마다 현재 상태 출력


		unit_setting(landing_priority, takeoff_priority, airport1_takeoff, airport1_landing,
			airport2_takeoff, airport2_landing, airport3, airport1_used, airport2_used, airport3_used_takeoff,
			air_1, air_2, air_3, air_4); 
		// 세팅 초기화 (airport_used 초기화 등). Sleep(1000)도 여기서 해결. 이륙장 초기화도 필요
		test_time--;
	}

	conclusion();
}

int main()
{
	test();

	return 0;
}