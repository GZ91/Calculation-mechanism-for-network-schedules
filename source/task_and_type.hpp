#pragma once
#include <string>
#include <ctime>

class Task;

enum class TypeBond { finish_start = 0, start_start = 1, start_finish = 2, finish_finish = 3 };

struct TaskAndType {
	TypeBond type_bond;
	unsigned long long key_task;
	std::time_t date_for_write;
};