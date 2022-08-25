#pragma once
#include <string>
#include <ctime>

class Task;

enum TypeBond { finish_start = 0, start_start = 1, start_finish = 2, finish_finish = 3 };

struct TaskAndType {
	std::shared_ptr<Task> task;
	TypeBond type_bond;
	std::string key_task;
	std::tm date_for_write;
};