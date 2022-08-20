#include "schedule.hpp"

Schedule::Schedule(json init_val, std::ostream& fst) {
	name = static_cast<std::string>(init_val[u8"Имя"]);
	date_plan = Schedule::Util::dt_from_json(init_val[u8"ДатаПлана"]);
	json tasks_json = init_val[u8"Операции"];
	for (json task_json : tasks_json) {
		auto task = std::make_shared<Schedule::Task>(task_json);
		tasks_map[task->get_key()] = task;
	}
}


void Schedule::execute_processing() {
	
}


