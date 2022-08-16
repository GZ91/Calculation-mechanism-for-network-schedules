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
	uint type_bond;
	std::string key_task;
	~TaskAndType() {
		delete task;
	}
	std::tm date_for_write;
};

enum TypeBond { finish_start = 0, start_start=1, start_finish=2, finish_finish=3 };

class Task {
public:
	Task(json &task_json)
	{
		
		lendth = static_cast<uint>(task_json[u8"ƒлит¬ћин"]);
		second_lendth = static_cast<std::time_t>(lendth * 60);
		ID = static_cast<std::string>(task_json[u8" одќп"]);
		key_calendate = static_cast<std::string>(task_json[u8" од алендар€"]);
		NestingLevel = static_cast<uint>(task_json[u8"”р¬лож"]);
		uint sum_int = static_cast<uint>(task_json[u8"—ум"]);
		sum = static_cast<bool>(sum_int);
		linkage_upload(task_json[u8"—в€зи"]);
		minimum_time_start_fact = convert_json_in_tm(task_json[u8"ћин‘акт"]);
		maximum_time_end_fact = convert_json_in_tm(task_json[u8"ћакс‘акт"]);
		begin_NRCH = convert_json_in_tm(task_json[u8"ЌачалоЌ–„"]);
	};


	std::string get_key() {
		return ID;
	}

	void fill_time_start_start(Task *task) {
		time_start.tm_sec = std::max(task->time_start.tm_sec, time_start.tm_sec);
	}
	
	void fill_time_finish_start(Task* task) {
		time_start.tm_sec = std::max(task->time_end.tm_sec, time_start.tm_sec);
	}
	
	void fill_time_start_finish(Task* task) {
		set_time_start_end(task->get_time_end());
	}
	
	void fill_time_finish_finish(Task* task) {
		time_end.tm_sec = std::max(task->time_end.tm_sec, time_end.tm_sec);
	}

	void fill_time() {
		for (auto task : followers)
		{
			if (task->type_bond == TypeBond::start_start) {
				task->task->fill_time_start_start(task->task);
			}
			else if (task->type_bond == TypeBond::finish_start)
			{
				task->task->fill_time_finish_start(task->task);
			}
			else if (task->type_bond == TypeBond::start_finish)
			{
				task->task->fill_time_start_finish(task->task);
			}
			else if (task->type_bond == TypeBond::finish_finish)
			{
				task->task->fill_time_finish_finish(task->task);
			}
		}
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

	bool its_not_prev_task() {
		return predecessors.empty();
	}

	std::tm get_time_end() {
		return time_end;
	}

	std::tm get_time_start() {
		return time_start;
	}

	
	bool set_time_start_end(std::tm val_tm)
	{
		
		std::time_t mval_tm		= std::mktime(&val_tm);
		std::time_t mtime_start = std::mktime(&time_start);
		if (mval_tm < mtime_start) return false; //если дата начала больше даты пришедшей, то отмена, т.к. дальнейший расчет по данному элементу и его последовател€м не нужен.
		
		std::time_t mtime_end	= std::mktime(&time_end);

		std::time_t mminimum_time_start = std::mktime(&minimum_time_start_fact);
		std::time_t mmaximum_time_end = std::mktime(&maximum_time_end_fact);


		std::time_t time_start_quest = std::max(mval_tm, mtime_start);
		std::time_t time_start_rec = std::max(time_start_quest, mminimum_time_start);


		std::time_t time_end_quest = std::max(time_start_rec + static_cast<time_t>(lendth * 60), mtime_end);
		std::time_t time_end_rec = std::max(time_end_quest, mmaximum_time_end);
		if (mmaximum_time_end != -1 && mmaximum_time_end < time_end_rec)
		{
			write_in_log("Exceeding the maximum late execution period. Task: " + ID);
		}
		
		second_start	= time_start_rec;
		second_end		= time_end_rec;
		
		time_start = *std::localtime(&time_start_rec);
		time_end = *std::localtime(&time_end_rec);
		return true;
	}


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

	std::time_t second_start;
	std::time_t second_end;
	std::time_t second_lendth;

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
		return std::tm{0};
	}
};