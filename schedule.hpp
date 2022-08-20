#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <strstream>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <chrono>
#include "nlohmann\json.hpp"


class Task;
enum TypeBond;
using json = nlohmann::json;
using ull = unsigned long long;
using uint = unsigned int;
using map_tasks = std::map<std::string, std::shared_ptr<Task>>;

class Schedule
{
public:
	explicit Schedule(json);
	std::chrono::milliseconds execute_processing();
	static void processing(Schedule *);
	json get_processed_chart();
private:
	map_tasks tasks_map;
	std::string name;
	std::tm date_plan;

	std::tm dt_from_str(std::string);
	std::tm dt_from_json(json);
	
	enum TypeBond { finish_start = 0, start_start = 1, start_finish = 2, finish_finish = 3 };
	class Task;
	struct TaskAndType {
		Task* task;
		uint type_bond;
		std::string key_task;
		std::tm date_for_write;
	};
	class Task {
	public:
		Task(json&);
		void fill_time();
		std::string get_key();
		std::vector<TaskAndType*>& get_followers();
		std::tm get_time_end();
		std::tm get_time_start();
		bool set_time_start_end(std::tm);
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

		void linkage_upload(json links);
	};
	static class util {
	public:
		static std::tm dt_from_str(std::string);
		static std::tm dt_from_json(json);
		static std::chrono::milliseconds time_measurement(void (*method)(Schedule* ), Schedule* obj);
	};
};