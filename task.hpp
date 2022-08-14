#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <strstream>


class Task;
enum class TypeBond;
using json = nlohmann::json;
using ull = unsigned long long;
using uint = unsigned int;
using set_task = std::map<std::string, Task*>;

struct TaskAndType {
	Task* task;
	TypeBond type_bond;
	std::string key_task;
};

enum class TypeBond { start_start, start_finish, finish_start, finish_finish };

class Task {
public:
	Task(json &task_json)
	{
		
		lendth = static_cast<uint>(task_json[u8"ДлитВМин"]);
		ID = static_cast<std::string>(task_json[u8"КодОп"]);
		key_calendate = static_cast<std::string>(task_json[u8"КодКалендаря"]);
		NestingLevel = static_cast<uint>(task_json[u8"УрВлож"]);
		uint sum_int = static_cast<uint>(task_json[u8"Сум"]);
		sum = static_cast<bool>(sum_int);
		linkage_upload(task_json[u8"Связи"]);
	};

	std::vector<TaskAndType*>& get_followers() {
		return followers;
	};

	void add_predecessor(TaskAndType* val_pred) {
		predecessors.push_back(val_pred);
	};

	void add_followers(TaskAndType* task) {
		followers.push_back(task);
	}

	std::vector <TaskAndType*>& get_predecessors() {
		return predecessors;
	};



private:

	std::string key_calendate;
	bool its_critical_task;
	uint NestingLevel;
	bool sum;
	uint lendth;
	std::tm time_start;
	std::tm time_end;

	std::tm minimum_time_start;
	std::tm maximum_time_end;

	std::vector <TaskAndType*> followers;
	std::vector <TaskAndType*> predecessors;
	std::string ID;

	void linkage_upload(json links) {
		for (auto link : links)
		{
			std::string key_prev = static_cast<std::string>(link[u8"КодПредш"]);
			TaskAndType* predec = new TaskAndType();
			predec->key_task = key_prev;
			predecessors.push_back(predec);
		}
	}
};