#pragma once
#include "task.hpp"

namespace tree {
	void link_elements(set_task s_tasks)
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

	std::vector<Task*> tasks_not_prev(set_task s_tasks) {
		std::vector<Task*> tasks_ret;
		for (auto task_map : s_tasks) {
			if (task_map.second->its_not_prev_task())
			{
				tasks_ret.push_back(task_map.second);
			}
		}
		return tasks_ret;
	}
}