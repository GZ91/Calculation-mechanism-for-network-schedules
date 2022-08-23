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
	process_with_the_dextra_algorithm();
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
		std::vector<std::shared_ptr<TaskAndType>> followers_(task->get_followers());
		for (auto task_follow : followers_) {
			auto itr_find = std::find(tasks.begin(), tasks.end(), task_follow);
			auto time_start_follow = std::mktime(&(task_follow->task->get_time_start()));
			auto time_end_this = std::mktime(&(task->get_time_end()));
			if (time_start_follow == -1 && time_end_this == -1)
			{
				Schedule::Util::write_in_log("Key: " + task->get_key() + " : Empty date comparison detected, probably an error - contact the developer." + ": follower : " + task_follow->task->get_key());
			}
			if (itr_find == tasks.end() && task_follow->type_bond == TypeBond::finish_start && time_start_follow < time_end_this) {
				tasks.push_back(task_follow);
				count++;
			}
				
		}
		++index;
	}
}

void Schedule::process_with_the_dextra_algorithm() {
	//const unsigned int size_map_tasks = tasks_map.size();
	//std::vector<std::shared_ptr<Task>> tasks;
	//for (auto task : tasks_map) {
	//	tasks.push_back(task.second);
	//}
	//std::vector <bool> visited(size_map_tasks, false);	
	//int index = 0, u = 0;
	//std::vector<std::vector<int>> w;
	//w.resize(size_map_tasks);
	//for (int i = 0; i < size_map_tasks; ++i)
	//	w[i].resize(size_map_tasks);

	//std::vector<int> D(size_map_tasks);
	//for (int i = 0; i < size_map_tasks; i++)
	//{
	//	D[i] = w[st][i];
	//	visited[i] = false;
	//}


	//for (int i = 0; i < size_map_tasks; i++)
	//{
	//	int min = INT_MAX;
	//	for (int j = 0; j < size_map_tasks; j++)
	//	{
	//		if (!visited[j] && D[j] < min)
	//		{
	//			min = D[j];
	//			index = j;
	//		}
	//	}
	//	u = index;
	//	visited[u] = true;
	//	for (int j = 0; j < size_map_tasks; j++)
	//	{
	//		if (!visited[j] && w[u][j] != INT_MAX && D[u] != INT_MAX && (D[u] + w[u][j] < D[j]))
	//		{
	//			D[j] = D[u] + w[u][j];
	//		}
	//	}
	//}




	////vector<vector<int >> w;
	////w.resize(n);
	//for (int i = 0; i < n; i++)
	//	w[i].resize(n);

	//bool visited[n];
	//int D[n];
	//for (int i = 0; i < n; i++)
	//{
	//	D[i] = w[st][i];
	//	visited[i] = false;
	//}
	//D[st] = 0;
	//int index = 0, u = 0;
	//for (int i = 0; i < n; i++)
	//{
	//	int min = INT_MAX;
	//	for (int j = 0; j < n; j++)
	//	{
	//		if (!visited[j] && D[j] < min)
	//		{
	//			min = D[j];
	//			index = j;
	//		}
	//	}
	//	u = index;
	//	visited[u] = true;
	//	for (int j = 0; j < n; j++)
	//	{
	//		if (!visited[j] && w[u][j] != INT_MAX && D[u] != INT_MAX && (D[u] + w[u][j] < D[j]))
	//		{
	//			D[j] = D[u] + w[u][j];
	//		}
	//	}
	//}
}