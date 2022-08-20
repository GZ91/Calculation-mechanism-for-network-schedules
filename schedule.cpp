#include "schedule.hpp"

Schedule::Schedule(json init_val) {
	name = static_cast<std::string>(init_val[u8"Имя"]);
	date_plan = Schedule::util::dt_from_json(init_val[u8"ДатаПлана"]);
	json tasks_json = init_val[u8"Операции"];
	for (json task_json : tasks_json) {
		auto task = std::make_shared<Schedule::Task>(task_json);
		tasks_map[task->get_key()] = task;
	}
}



std::tm Schedule::util::dt_from_str(std::string str)
{
	std::wstring wstr_date_plan(str.begin(), str.end());
	static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	std::wistringstream ss{ wstr_date_plan };
	std::tm dt;
	ss >> std::get_time(&dt, dateTimeFormat.c_str());
	return dt;
}

std::tm Schedule::util::dt_from_json(json val)
{
	if (val.is_null()) return std::tm();
	return dt_from_str(static_cast<std::string>(val));
}

std::chrono::milliseconds Schedule::util::time_measurement(void (*method)(Schedule*), Schedule *obj) {
	auto start = std::chrono::high_resolution_clock::now();
	method(obj);
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

std::chrono::milliseconds Schedule::execute_processing() {
	return util::time_measurement(processing, this);
}

void Schedule::processing(Schedule *obj)
{

}

Schedule::Task::Task(json& task_json)
{
	lendth = static_cast<uint>(task_json[u8"ДлитВМин"]);
	second_lendth = static_cast<std::time_t>(lendth * 60);
	ID = static_cast<std::string>(task_json[u8"КодОп"]);
	key_calendate = static_cast<std::string>(task_json[u8"КодКалендаря"]);
	NestingLevel = static_cast<uint>(task_json[u8"УрВлож"]);
	uint sum_int = static_cast<uint>(task_json[u8"Сум"]);
	sum = static_cast<bool>(sum_int);
	linkage_upload(task_json[u8"Связи"]);
	minimum_time_start_fact = Schedule::util::dt_from_json(task_json[u8"МинФакт"]);
	maximum_time_end_fact = Schedule::util::dt_from_json(task_json[u8"МаксФакт"]);
	begin_NRCH = Schedule::util::dt_from_json(task_json[u8"НачалоНРЧ"]);
}

Schedule::Task::~Task() {
	
}

void Schedule::Task::linkage_upload(json links) {
	for (auto link : links)
	{
		std::string key_prev = static_cast<std::string>(link[u8"КодПредш"]);
		auto predec = std::make_shared<TaskAndType>();
		predec->key_task = key_prev;
		predec->type_bond = link[u8"ВидСвязи"].is_null() ? static_cast<TypeBond>(0) : static_cast<TypeBond>(static_cast<uint>(link[u8"ВидСвязи"])); //получаю из числа вид связи
		predecessors.push_back(predec);
	}
}

std::string Schedule::Task::get_key()
{
	return ID;
}