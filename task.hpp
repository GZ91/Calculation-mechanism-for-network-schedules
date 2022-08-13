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
using set_task = std::map<ull, Task*>;

struct TaskAndType {
	Task* task;
	TypeBond type_bond;
};

enum class TypeBond { start_start, start_finish, finish_start, finish_finish };

class Task {
public:
	Task(uint lendth, ull ID, std::string key_calen) :lendth{ lendth }, ID{ ID }, its_critical_task{ false }, key_calendate{ key_calen } {};

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

	uint lendth;
	std::tm time_start;
	std::tm time_end;

	std::tm minimum_time_start;
	std::tm maximum_time_end;

	std::vector <TaskAndType*> followers;
	std::vector <ull> predecessors;
	ull ID;
};