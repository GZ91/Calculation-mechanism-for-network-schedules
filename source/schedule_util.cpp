#include "schedule.hpp"
std::string Schedule::Util::name_log_file = "";

std::tm Schedule::Util::dt_from_str(std::string str)
{
	std::wstring wstr_date_plan(str.begin(), str.end());
	static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	std::wistringstream ss{ wstr_date_plan };
	std::tm dt;
	ss >> std::get_time(&dt, dateTimeFormat.c_str());
	return dt;
}

std::tm Schedule::Util::dt_from_json(json val)
{
	if (val.is_null()) return std::tm();
	return dt_from_str(static_cast<std::string>(val));
}

std::chrono::milliseconds Schedule::Util::time_measurement(void (*method)()) {
	auto start = std::chrono::high_resolution_clock::now();
	method();
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

void Schedule::Util::write_in_log(std::string text_log, int type_error) {
	std::fstream log_f(name_log_file, std::ios::app);
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	std::string end = "";
	if (type_error != 0) {
		end = " @program crash@";
	}
	log_f << end << text_log << " % " << asctime(timeinfo);
	log_f.close();
	if (type_error != 0) {
		exit(type_error);
	}
}

void Schedule::Util::create_name_log_file(std::string new_name) {
	Schedule::Util::name_log_file = new_name;
}