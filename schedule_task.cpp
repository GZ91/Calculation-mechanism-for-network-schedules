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
	print_error("The element was successfully created");
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

std::string Schedule::Task::get_key()
{
	return ID;
}

void Schedule::Task::print_error(std::string text_error, int type_error) {
	Schedule::Util::write_in_log("Key: " + get_key() + " :" + text_error, type_error);
}