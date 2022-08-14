#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <strstream>
#include "log.hpp"
#include "util.hpp"


class Task;
enum TypeBond;
using json = nlohmann::json;
using ull = unsigned long long;
using uint = unsigned int;
using set_task = std::map<std::string, Task*>;

struct TaskAndType {
	Task* task;
	TypeBond type_bond;
	std::string key_task;
	~TaskAndType() {
		delete task;
	}
};

enum TypeBond { start_start=0, start_finish=1, finish_start=2, finish_finish=3 };

class Task {
public:
	Task(json &task_json)
	{
		
		lendth = static_cast<uint>(task_json[u8"ƒлит¬ћин"]);
		ID = static_cast<std::string>(task_json[u8" одќп"]);
		key_calendate = static_cast<std::string>(task_json[u8" од алендар€"]);
		NestingLevel = static_cast<uint>(task_json[u8"”р¬лож"]);
		uint sum_int = static_cast<uint>(task_json[u8"—ум"]);
		sum = static_cast<bool>(sum_int);
		linkage_upload(task_json[u8"—в€зи"]);
		minimum_time_start_fact = convert_json_in_tm(task_json[u8"ћин‘акт"]);
		maximum_time_end_fact = convert_json_in_tm(task_json[u8"ћакс‘акт"]);
		begin_NRCH = convert_json_in_tm(task_json[u8"ћакс‘акт"]);
	};

	~Task() {
		for (auto link : predecessors)
		{
			delete link;
		}
		for (auto link : followers)
		{
			delete link;
		}
	}

	std::string get_key() {
		return ID;
	}

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

	std::tm minimum_time_start_fact;
	std::tm maximum_time_end_fact;
	std::tm begin_NRCH;

	std::vector <TaskAndType*> followers;
	std::vector <TaskAndType*> predecessors;
	std::string ID;

	void linkage_upload(json links) {
		for (auto link : links)
		{
			std::string key_prev = static_cast<std::string>(link[u8" одѕредш"]);
			TaskAndType* predec = new TaskAndType();
			predec->key_task = key_prev;
			predec->type_bond = link[u8"¬ид—в€зи"].is_null() ? static_cast<TypeBond>(0) : static_cast<TypeBond>(static_cast<uint>(link[u8"¬ид—в€зи"])); //получаю из числа вид св€зи
			predecessors.push_back(predec);
		}
	}

	std::tm convert_json_in_tm(json val) {
		if (val.is_string()) {
			std::string tm_str = static_cast<std::string>(val);
			return util::dt_from_str(tm_str);
		}
		return std::tm();
	}
};