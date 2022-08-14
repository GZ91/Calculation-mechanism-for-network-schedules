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
};

enum class TypeBond { start_start, start_finish, finish_start, finish_finish };

class Task {
public:
	Task(json &_lendth, json &_ID, json &_key_calen, json &_NestingLvl, json &_sum)
	{
		lendth = static_cast<uint>(_lendth);
		ID = static_cast<std::string>(_ID);
		key_calendate = static_cast<std::string>(_key_calen);
		NestingLevel = static_cast<uint>(_NestingLvl);
		uint sum_int = static_cast<uint>(_sum);
		sum = static_cast<bool>(sum_int);
	};

	std::vector<TaskAndType*>& get_followers() {
		return followers;
	};

	void add_predecessor(ull val_pred) {
		predecessors.push_back(val_pred);
	};

	void add_followers(TaskAndType* task) {
		followers.push_back(task);
	}

	std::vector <ull>& get_predecessors() {
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
	std::vector <ull> predecessors;
	std::string ID;
};