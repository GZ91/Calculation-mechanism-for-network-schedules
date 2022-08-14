#include <iostream>
#include <fstream>
#include "nlohmann\json.hpp"
#include <sstream>
#include "task.hpp"
#include "util.hpp"
#include "log.hpp"
#include "tree.hpp"





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
	std::vector<Task*> tasks_not_prev = tree::tasks_not_prev(tasks_map);
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

}




	//std::string str_date_plan = static_cast<std::string>(date_plan);
	//std::wstring wstr_date_plan(str_date_plan.begin(), str_date_plan.end());
	//static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	//std::wistringstream ss{ wstr_date_plan };
	//std::tm dt;
	//ss >> std::get_time(&dt, dateTimeFormat.c_str());
	//std::tm dt = dt_from_str(static_cast<std::string>(date_plan));
	//auto mktime = std::mktime(&dt);
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
	//dt.tm_sec += 1;
	//mktime = std::mktime(&dt);
	//std::cout << mktime << '\n' << dt.tm_mon << '\n';
	//return 0;

	//static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	//std::wistringstream ss{ date_plan };
	//std::tm dt;
	//ss >> std::get_time(&dt, dateTimeFormat.c_str());
	//auto mktime = std::mktime(&dt);
	////detect_type_val(status);
	//std::cout << status << '\n' << message << '\n' << mktime << std::endl;
	//return 0;


