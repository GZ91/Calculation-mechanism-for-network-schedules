#pragma once
#include "task.hpp"

namespace tree {
	void link_elements(set_task s_tasks) // Связываем элементы - заполняем ссылки в предшественниках и в них же заполняем последователя - текущую ссылку на задачу.
	{
		for (auto task_map : s_tasks) {
			auto predecessors = task_map.second->get_predecessors();
			for (auto predecessor : predecessors) {
				predecessor->task = s_tasks[predecessor->key_task];
				TaskAndType* TAT = new TaskAndType;
				TAT->task = task_map.second;
				TAT->key_task = task_map.first;
				TAT->type_bond = predecessor->type_bond;
				predecessor->task->add_followers(TAT);
			}
		}
	}

	std::vector<TaskAndType*> tasks_not_prev(set_task s_tasks, json date_plan) { // Возвращает вектор задач без предшественников
		std::vector<TaskAndType*> tasks_ret;
		for (auto task_map : s_tasks) {
			if (task_map.second->its_not_prev_task())
			{
				TaskAndType* T = new TaskAndType;
				T->task = task_map.second;
				T->type_bond = TypeBond::finish_start;
				T->date_for_write = util::dt_from_str(static_cast<std::string>(date_plan));
				tasks_ret.push_back(T);
			}
		}
		return tasks_ret;
	}

	void tree_fill_time(std::vector<TaskAndType*> s_tasks) { // по задумке эта функция должна заполнять время в задачах, но нужно разобраться с алгоритмом заполнения. Ещё раз всё продумать
		std::vector<TaskAndType*> tasks(s_tasks);
	
		uint count = tasks.size();
		uint index = 0;
		while (count > index)
		{
			auto task = tasks[index]->task;
			
			if (tasks[index]->type_bond  == TypeBond::finish_start && !task->set_time_start_end(tasks[index]->date_for_write)) {
				++index;
				continue;
			}
			auto followers = task->get_followers();
			for (auto task_follow : followers) {
				auto itr_find = std::find(tasks.begin(), tasks.end(), task_follow);
				if (itr_find != tasks.end())write_in_log("A loop in the graph on the problem is detected: " + task_follow->key_task + ", inside the task: " + tasks[index]->key_task,1);
				task_follow->date_for_write = task->get_time_end();
			}
			tasks.insert(tasks.end(), followers.begin(), followers.end());
			count += followers.size();
			++index;
		}
	}
}