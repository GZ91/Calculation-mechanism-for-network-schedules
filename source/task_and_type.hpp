#pragma once
#include <string>
#include <ctime>


enum class TypeBond { finish_start = 0, start_start = 1, start_finish = 2, finish_finish = 3 }; // типы связей

struct TaskAndType {
	TypeBond type_bond; // тип связи
	unsigned long long key_task; // ключ задачи
	std::time_t date_end_for_write; // дата конца для записи - используется в случае записи времени задачи
	std::time_t date_start_for_write; // дата старта для записи - используется в случае записи времени задачи
};