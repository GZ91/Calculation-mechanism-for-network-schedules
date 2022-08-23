#include "schedule.hpp"

Schedule::Task::Task(json& task_json)
{
	lendth = static_cast<uint>(task_json[u8"��������"]);
	second_lendth = static_cast<std::time_t>(lendth * 60);
	ID = static_cast<std::string>(task_json[u8"�����"]);
	key_calendate = static_cast<std::string>(task_json[u8"������������"]);
	NestingLevel = static_cast<uint>(task_json[u8"������"]);
	uint sum_int = static_cast<uint>(task_json[u8"���"]);
	sum = static_cast<bool>(sum_int);
	linkage_upload(task_json[u8"�����"]);
	minimum_time_start_fact = Schedule::Util::dt_from_json(task_json[u8"�������"]);
	maximum_time_end_fact = Schedule::Util::dt_from_json(task_json[u8"��������"]);
	begin_NRCH = Schedule::Util::dt_from_json(task_json[u8"���������"]);
}

Schedule::Task::~Task() {
}

void Schedule::Task::linkage_upload(json links) {
	for (auto link : links)
	{
		std::string key_prev = static_cast<std::string>(link[u8"��������"]);
		auto predec = std::make_shared<TaskAndType>();
		predec->key_task = key_prev;
		predec->type_bond = link[u8"��������"].is_null() ? static_cast<TypeBond>(0) : static_cast<TypeBond>(static_cast<uint>(link[u8"��������"])); //������� �� ����� ��� �����
		predecessors.push_back(predec);
	}
}

std::vector <std::shared_ptr<Schedule::TaskAndType>>& Schedule::Task::get_predecessors() {
	return predecessors;
};

std::vector <std::shared_ptr<Schedule::TaskAndType>>& Schedule::Task::get_followers() {
	return followers;
};

std::string Schedule::Task::get_key()
{
	return ID;
}

void Schedule::Task::print_error(std::string text_error, int type_error) {
	Schedule::Util::write_in_log("Key: " + get_key() + " :" + text_error, type_error);
}

void Schedule::Task::add_followers(std::shared_ptr<TaskAndType> task) {
	followers.push_back(task);
}

bool Schedule::Task::its_not_prev_task() {
	return predecessors.empty();
}

bool Schedule::Task::set_time_start_end(std::tm val_tm)
{

	std::time_t mval_tm = std::mktime(&val_tm);
	std::time_t mtime_start = std::mktime(&time_start);
	if (mval_tm < mtime_start) return false; //���� ���� ������ ������ ���� ���������, �� ������, �.�. ���������� ������ �� ������� �������� � ��� �������������� �� �����.

	std::time_t mtime_end = std::mktime(&time_end);

	std::time_t mminimum_time_start = std::mktime(&minimum_time_start_fact);
	std::time_t mmaximum_time_end = std::mktime(&maximum_time_end_fact);


	std::time_t time_start_quest = std::max(mval_tm, mtime_start);
	std::time_t time_start_rec = std::max(time_start_quest, mminimum_time_start);


	std::time_t time_end_quest = std::max(time_start_rec + static_cast<time_t>(lendth * 60), mtime_end);
	std::time_t time_end_rec = std::max(time_end_quest, mmaximum_time_end);
	if (mmaximum_time_end != -1 && mmaximum_time_end < time_end_rec)
	{
		Util::write_in_log("Exceeding the maximum late execution period. Task: " + ID);
	}

	second_start = time_start_rec;
	second_end = time_end_rec;

	time_start = *std::localtime(&time_start_rec);
	time_end = *std::localtime(&time_end_rec);
	return true;
}

std::tm Schedule::Task::get_time_end() {
	return time_end;
}

std::tm Schedule::Task::get_time_start() {
	return time_start;
}