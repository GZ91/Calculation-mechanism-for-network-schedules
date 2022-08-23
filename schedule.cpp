#include "schedule.hpp"

Schedule::Schedule(json init_val, std::string logovo) {
	Schedule::Util::create_name_log_file(logovo);
	name = static_cast<std::string>(init_val[u8"Имя"]);
	date_plan = Schedule::Util::dt_from_json(init_val[u8"ДатаПлана"]);
	json tasks_json = init_val[u8"Операции"];

	for (json task_json : tasks_json) {
		std::shared_ptr<Schedule::Task> _task = std::make_shared<Schedule::Task>(task_json);
		auto key = _task->get_key();
		tasks_map[key] = _task;
	}
	link_elements(tasks_map);
}

Schedule::~Schedule() {
	for (auto w_ptr : tasks_map)
	{
		w_ptr.second->~Task();
	}
}


void Schedule::execute_processing() {
	std::vector<std::shared_ptr<Schedule::TaskAndType>> not_prev_TATS = tasks_not_prev();
	tree_fill_time(not_prev_TATS);
}

void Schedule::link_elements(map_tasks s_tasks)
{
	for (auto task_map : s_tasks) {
		auto predecessors = task_map.second->get_predecessors();
		for (auto predecessor : predecessors) {
			predecessor->task = s_tasks[predecessor->key_task];
			auto TAT = std::make_shared<TaskAndType>();
			TAT->task = s_tasks[predecessor->key_task];
			TAT->key_task = task_map.first;
			TAT->type_bond = predecessor->type_bond;
			predecessor->task->add_followers(TAT);
		}
	}
}

std::vector<std::shared_ptr<Schedule::TaskAndType>> Schedule::tasks_not_prev() {
	std::vector <std::shared_ptr<TaskAndType>> tasks_ret;
	for (auto task_map : tasks_map) {
		if (task_map.second->its_not_prev_task()){
			std::shared_ptr<TaskAndType> T = std::make_shared<TaskAndType>();
			T->task = task_map.second;
			T->type_bond = TypeBond::finish_start;
			T->date_for_write = date_plan;
			tasks_ret.push_back(T);
		}
	}
	return tasks_ret;
}

void Schedule::tree_fill_time(std::vector<std::shared_ptr<Schedule::TaskAndType>> s_tasks) {
	std::vector<std::shared_ptr<Schedule::TaskAndType>> tasks(s_tasks);
	uint count = tasks.size();
	uint index = 0;
	while (count > index)
	{
		auto task = tasks[index]->task;
		if (tasks[index]->type_bond == TypeBond::finish_start && !task->set_time_start_end(tasks[index]->date_for_write)) {
			++index;
			continue;
		}
		auto followers = task->get_followers();
		for (auto task_follow : followers) {
			auto itr_find = std::find(tasks.begin(), tasks.end(), task_follow);
			if (itr_find != tasks.end()) 
				followers.erase(itr_find);
		}
		tasks.insert(tasks.end(), followers.begin(), followers.end());
		count += followers.size();
		++index;
	}
}