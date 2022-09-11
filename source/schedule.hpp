#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <map>
#include "nlohmann\json.hpp"
#include "task.hpp"
#include "task_and_type.hpp"
#include "util.hpp"

using json = nlohmann::json;
using map_tasks = std::map<unsigned long long, std::shared_ptr<Task>>;

class Schedule
{
public:
	explicit Schedule(json, std::string); 
	~Schedule();
	void execute_processing(); // запуск вычислений
	json get_processed_chart();

private:
	map_tasks tasks_map; // map задач номер / task
	std::string name; // имя графика
	std::time_t date_plan; // плановая дата начала графика
	void Schedule::link_elements(map_tasks); // соединяет элементы между собой, строит таблицу связей
	std::vector<std::shared_ptr<TaskAndType>> tasks_not_prev(); // поиск начал графика
	void process_with_the_dextra_algorithm(); // применение алгоритма дейкстры для графика
	void tree_fill_time(std::vector<std::shared_ptr<TaskAndType>>); // заполняем время элементов
	std::vector<std::vector<int>> matrix_adjacency_prev; // таблица связей 
};