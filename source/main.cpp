#include "schedule.hpp"


void test_function() {
	std::ifstream f("..\\..\\..\\resource.json");
	if (f.fail()) exit(1); //Если файл не найден
	json data = json::parse(f);
	f.close();
	Schedule sch(data, "logovo.txt");
	sch.execute_processing();
}


int main() {
	for (int i = 0; i < 1000000; ++i) { //memory leak test
		auto time_proc = Schedule::Util::time_measurement(test_function);
		auto time_count = static_cast<double>(time_proc.count());
		time_count /= 1000;
		std::cout << "Time: " << time_count << " sec\n" << std::endl;
	}
}





















//time_t seconds = time(NULL);
//tm* timeinfo = localtime(&seconds);
//timeinfo->tm_min++;
//timeinfo->tm_wday += 3;
//seconds = std::mktime(timeinfo);
//
//time_t seconds_2 = time(NULL);
//tm* timeinfo_2 = localtime(&seconds_2);
//timeinfo_2->tm_min += 2;
//timeinfo_2->tm_wday += 3;
//seconds_2 = std::mktime(timeinfo_2);
//
//std::cout << timeinfo << std::endl;
//std::cout << timeinfo_2 << std::endl;
//
//if (seconds < seconds_2)std::cout << "All good" << std::endl;
//if (seconds == seconds_2)std::cout << "All bed" << std::endl;


/*#include <iostream>
#include <fstream>
#include "nlohmann\json.hpp"
#include <sstream>
#include "task.hpp"
#include "util.hpp"
#include "log.hpp"
#include "tree.hpp"
*/






/*
void time_method() {
	std::ifstream f("..\\..\\..\\resource.json");
	if (f.fail()) exit(1); //Если файл не найден
	json data = json::parse(f);
	auto name = data[u8"Имя"];
	auto date_plan = data[u8"ДатаПлана"];
	auto tasks_json = data[u8"Операции"];
	set_task tasks_map;
	for (auto task_json : tasks_json) {

		Task* task = new Task(task_json);
		tasks_map[task->get_key()] = task;
	}
	///
	tree::link_elements(tasks_map);
	std::vector<TaskAndType*> tasks_not_prev = tree::tasks_not_prev(tasks_map, date_plan);

	tree::tree_fill_time(tasks_not_prev);
	///
	for (auto link : tasks_map) {
		delete link.second;
	}
}




int main()
{
	auto time_proc = util::time_measurement(time_method);
	auto time_count = static_cast<double>(time_proc.count());
	time_count /= 1000;
	std::cout << "Time: " << time_count << " sec\n";


	return 0;

}*/


	// в процессе разработки..
	// ЗДЕСЬ тестовые кусочки
	//std::ifstream f("..\\..\\..\\resource.json");
	//if (f.fail()) exit(1); //Если файл не найден
	//json data = json::parse(f);
	/*std::string str_date_plan = static_cast<std::string>(data[u8"ДатаПлана"]);
	std::wstring wstr_date_plan(str_date_plan.begin(), str_date_plan.end());
	static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	std::wistringstream ss{ wstr_date_plan };
	std::tm dt;
	ss >> std::get_time(&dt, dateTimeFormat.c_str());*/
	//std::tm dt = util::dt_from_str(static_cast<std::string>(data[u8"ДатаПлана"]));
	//std::time_t mktime = std::mktime(&dt);
	//std::cout << mktime << '\n' << dt.tm_mon << '\n';
	//dt.tm_mday += 1;
	//mktime = std::mktime(&dt);
	//std::cout << mktime << '\n' << dt.tm_mon << '\n';
	//dt.tm_mon += 1;
	//mktime = std::mktime(&dt);
	//std::cout << mktime << '\n' << dt.tm_mon << '\n';
	//dt.tm_year += 10;
	//mktime = std::mktime(&dt);
	//std::cout << mktime << '\n' << dt.tm_mon << '\n';
	//dt.tm_min += 1;
	//mktime = std::mktime(&dt);
	//std::cout << mktime << '\n' << dt.tm_mon << '\n';
	//dt.tm_sec += 71;
	//mktime = std::mktime(&dt);
	//std::cout << mktime << '\n' << dt.tm_mon << '\n';
	//
	//std::cout << "test:" << dt.tm_isdst << '\n';

	//std::tm dt = util::dt_from_str(static_cast<std::string>(data[u8"ДатаПлана"]));
	//std::cout << std::put_time(&dt, "%c %Z") << '\n';
	//std::time_t mktime = std::mktime(&dt);
	//mktime += 86400;
	//dt = *std::localtime(&mktime);
	//std::cout << std::put_time(&dt, "%c %Z") << '\n';
	//mktime = std::mktime(&dt);
	//mktime += 86400*30;
	//dt = *std::localtime(&mktime);
	//std::cout << std::put_time(&dt, "%c %Z") << '\n';


	//return 0;

	//static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	//std::wistringstream ss{ date_plan };
	//std::tm dt;
	//ss >> std::get_time(&dt, dateTimeFormat.c_str());
	//auto mktime = std::mktime(&dt);
	////detect_type_val(status);
	//std::cout << status << '\n' << message << '\n' << mktime << std::endl;
	//return 0;

//}
