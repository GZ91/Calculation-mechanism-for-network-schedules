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
	void execute_processing();
	json get_processed_chart();

private:
		
	map_tasks tasks_map;
	std::string name;
	std::time_t date_plan;
	void Schedule::link_elements(map_tasks, std::vector<std::vector<bool>>);
	std::vector<std::shared_ptr<TaskAndType>> tasks_not_prev();
	void process_with_the_dextra_algorithm();
	void tree_fill_time(std::vector<std::shared_ptr<TaskAndType>>);
};