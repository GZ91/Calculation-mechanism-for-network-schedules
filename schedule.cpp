#include "schedule.hpp"

Schedule::Schedule(json init_val, std::ostream& fst) {
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

