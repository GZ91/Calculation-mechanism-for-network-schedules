#include "task.hpp"
#include "util.hpp"
#include "task_and_type.hpp"

Task::Task(json& task_json)
{
	unsigned int lendth = static_cast<unsigned int>(task_json[u8"ƒлит¬ћин"]);
	second_lendth = static_cast<std::time_t>(lendth * 60);
	ID = stoull(static_cast<std::string>(task_json[u8" одќп"]));
	key_calendate = static_cast<std::string>(task_json[u8" од алендар€"]);
	NestingLevel = static_cast<unsigned int>(task_json[u8"”р¬лож"]);
	unsigned int sum_int = static_cast<unsigned int>(task_json[u8"—ум"]);
	sum = static_cast<bool>(sum_int);
	linkage_upload(task_json[u8"—в€зи"]);
	minimum_time_start_fact = Util::time_t_from_json(task_json[u8"ћин‘акт"]);
	maximum_time_end_fact = Util::time_t_from_json(task_json[u8"ћакс‘акт"]);
	begin_NRCH = Util::time_t_from_json(task_json[u8"ЌачалоЌ–„"]);
}

Task::~Task() {
}

void Task::linkage_upload(json links) {
	for (auto link : links)
	{
		unsigned long long key_prev = stoull(static_cast<std::string>(link[u8" одѕредш"]));
		auto predec = std::make_shared<TaskAndType>();
		predec->key_task = key_prev;
		predec->type_bond = link[u8"¬ид—в€зи"].is_null() ? static_cast<TypeBond>(0) : static_cast<TypeBond>(static_cast<unsigned int>(link[u8"¬ид—в€зи"])); //получаю из числа вид св€зи
		predecessors.push_back(predec);
	}
}

std::vector <std::shared_ptr<TaskAndType>>& Task::get_predecessors() {
	return predecessors;
};

std::vector <std::shared_ptr<TaskAndType>>& Task::get_followers() {
	return followers;
};

unsigned long long Task::get_key()
{
	return ID;
}

void Task::print_error(std::string text_error, int type_error) {
	Util::write_in_log("Key: " + std::to_string(get_key()) + " :" + text_error, type_error);
}

void Task::add_followers(std::shared_ptr<TaskAndType> task) {
	followers.push_back(task);
}

bool Task::its_not_prev_task() {
	return predecessors.empty();
}

bool Task::set_time_start_end(std::time_t val_tm)
{

	std::time_t mval_tm = val_tm;
	std::time_t mtime_start = second_start;
	if (mval_tm < mtime_start) return false; //если дата начала больше даты пришедшей, то отмена, т.к. дальнейший расчет по данному элементу и его последовател€м не нужен.

	std::time_t mtime_end = second_end;

	std::time_t mminimum_time_start = minimum_time_start_fact;
	std::time_t mmaximum_time_end = maximum_time_end_fact;


	std::time_t time_start_quest = std::max(mval_tm, mtime_start);
	std::time_t time_start_rec = std::max(time_start_quest, mminimum_time_start);


	std::time_t time_end_quest = std::max(time_start_rec + second_lendth, mtime_end);
	std::time_t time_end_rec = std::max(time_end_quest, mmaximum_time_end);
	if (mmaximum_time_end != -1 && mmaximum_time_end < time_end_rec)
	{
		Util::write_in_log("Exceeding the maximum late execution period. Task: " + ID);
	}

	second_start = time_start_rec;
	second_end = time_end_rec;

	return true;
}

std::time_t Task::get_time_end() {
	return second_end;
}

std::time_t Task::get_time_start() {
	return second_start;
}