#pragma once
#include <ctime>
#include <string>
#include <vector>
#include "nlohmann\json.hpp"
#include "task_and_type.hpp"

using json = nlohmann::json;

class Task {
public:
	explicit Task(json&);
	Task(Task&) = delete;
	Task& operator=(Task&) = delete;
	~Task();
	void fill_time();
	unsigned long long get_key();
	std::vector<std::shared_ptr<TaskAndType>>& get_followers();
	std::vector <std::shared_ptr<TaskAndType>>& get_predecessors();
	std::time_t get_time_end();
	std::time_t get_time_start();
	bool set_time_start_end(std::time_t);
	void add_followers(std::shared_ptr<TaskAndType> task);
	bool its_not_prev_task();
private:
	unsigned long long ID;
	
	
	std::string key_calendate;
	bool its_critical_task;
	int NestingLevel;
	bool sum;

	std::vector <std::shared_ptr<TaskAndType>> followers;
	std::vector <std::shared_ptr<TaskAndType>> predecessors;
	
	std::time_t minimum_time_start_fact;
	std::time_t maximum_time_end_fact;
	std::time_t begin_NRCH;
	std::time_t second_start;
	std::time_t second_end;
	std::time_t second_lendth;

	void linkage_upload(json links);

	void print_error(std::string text_error, int type_error = 0);
};