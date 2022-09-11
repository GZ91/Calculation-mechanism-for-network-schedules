#include "schedule.hpp"

Schedule::Schedule(json init_val, std::string logovo) {
	Util::create_name_log_file(logovo);
	name = static_cast<std::string>(init_val[u8"Имя"]);
	date_plan = Util::time_t_from_json(init_val[u8"ДатаПлана"]);
	json tasks_json = init_val[u8"Операции"];

	unsigned long long max_key = 0;
	for (json task_json : tasks_json) {
		std::shared_ptr<Task> _task = std::make_shared<Task>(task_json);
		auto key = _task->get_key();
		tasks_map[key] = _task;
		if (max_key < key) {
			max_key = key;
		}
	}
	
	
	for (unsigned long long i = 0; i <= max_key; ++i) {
		std::vector<int> m;
		for (unsigned long long y = 0; y <= max_key; ++y) {
			m.push_back(0);
		}
		matrix_adjacency_prev.push_back(m);
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
	std::vector<std::shared_ptr<TaskAndType>> not_prev_TATS = tasks_not_prev();
	tree_fill_time(not_prev_TATS);
	process_with_the_dextra_algorithm();
}

void Schedule::link_elements(map_tasks s_tasks)
{
	for (auto task_map : s_tasks) {
		auto predecessors = task_map.second->get_predecessors();
		for (auto& predecessor : predecessors) {
			matrix_adjacency_prev[task_map.first][predecessor->key_task] = 1; // 1 = связь окончание_начало
			auto TAT = std::make_shared<TaskAndType>();
			TAT->key_task = task_map.first;
			TAT->type_bond = predecessor->type_bond;
			s_tasks[predecessor->key_task]->add_followers(TAT);
		}
	}
}

std::vector<std::shared_ptr<TaskAndType>> Schedule::tasks_not_prev() {
	std::vector <std::shared_ptr<TaskAndType>> tasks_ret;
	for (auto task_map : tasks_map) {
		if (task_map.second->its_not_prev_task()){
			std::shared_ptr<TaskAndType> T = std::make_shared<TaskAndType>();
			T->key_task = task_map.first; 
			T->type_bond = TypeBond::finish_start; // заменить на нормальное считывание типа связи
			T->date_end_for_write = date_plan;
			tasks_ret.push_back(T);
		}
	}
	return tasks_ret;
}

void Schedule::tree_fill_time(std::vector<std::shared_ptr<TaskAndType>> s_tasks) {
	std::vector<std::shared_ptr<TaskAndType>> tasks(s_tasks);
	unsigned int count = tasks.size();
	unsigned int index = 0;
	while (count > index)
	{
		auto task = tasks_map[tasks[index]->key_task];
		if (tasks[index]->type_bond == TypeBond::finish_start && !task->set_time_end_start(tasks[index]->date_end_for_write)) {
			++index;
			continue;
		}
		// методы обработки других связей должны быть здесь

		std::vector<std::shared_ptr<TaskAndType>> followers_(task->get_followers());
		for (auto task_follow : followers_) {
			auto itr_find = std::find(tasks.begin() + index, tasks.end(), task_follow);
			auto time_start_follow = tasks_map[task_follow->key_task]->get_time_start();
			auto time_end_this = tasks_map[task_follow->key_task]->get_time_end();
			task_follow->date_end_for_write = task->get_time_end();
			task_follow->date_start_for_write = task->get_time_start();
			if (time_start_follow == -1 && time_end_this == -1) //проверка на ошибку дат
			{
				std::string tmp = "";
				tmp += "Key: ";
				tmp += task->get_key();
				tmp += " : Empty date comparison detected, probably an error - contact the developer. : follower : ";
				tmp += tasks_map[task_follow->key_task]->get_key();
				Util::write_in_log(tmp);
			}
			if (itr_find == tasks.end() &&  time_start_follow < time_end_this) {//
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