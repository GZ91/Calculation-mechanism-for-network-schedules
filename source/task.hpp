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
	~Task();
	void fill_time();
	std::string get_key();
	std::vector<std::shared_ptr<TaskAndType>>& get_followers();
	std::vector <std::shared_ptr<TaskAndType>>& get_predecessors();
	std::tm get_time_end();
	std::tm get_time_start();
	bool set_time_start_end(std::tm);
	void add_followers(std::shared_ptr<TaskAndType> task);
	bool its_not_prev_task();
private:
	std::string key_calendate;
	bool its_critical_task;
	int NestingLevel;
	bool sum;
	unsigned long long lendth;
	std::tm time_start;
	std::tm time_end;

	std::tm minimum_time_start_fact;
	std::tm maximum_time_end_fact;
	std::tm begin_NRCH;

	std::vector <std::shared_ptr<TaskAndType>> followers;
	std::vector <std::shared_ptr<TaskAndType>> predecessors;
	std::string ID;

	std::time_t second_start;
	std::time_t second_end;
	std::time_t second_lendth;

	void linkage_upload(json links);

	void print_error(std::string text_error, int type_error = 0);
};