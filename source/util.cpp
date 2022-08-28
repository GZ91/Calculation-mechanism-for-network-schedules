#include "util.hpp"

std::string name_log_file = "";

std::tm Util::dt_from_str(std::string str)
{
	std::wstring wstr_date_plan(str.begin(), str.end());
	static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	std::wistringstream ss{ wstr_date_plan };
	std::tm dt;
	ss >> std::get_time(&dt, dateTimeFormat.c_str());
	return dt;
}

std::tm Util::dt_from_json(json val)
{
	if (val.is_null()) return std::tm();
	return dt_from_str(static_cast<std::string>(val));
}

std::time_t Util::time_t_from_json(json val) {
	if (val.is_null()) return time(0);
	auto dt = dt_from_str(static_cast<std::string>(val));
	return mktime(&dt);
}

std::chrono::milliseconds Util::time_measurement(void (*method)()) {
	auto start = std::chrono::high_resolution_clock::now();
	method();
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

void Util::write_in_log(std::string text_log, int type_error) {
	std::fstream log_f(Util::name_log_file, std::ios::app);
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

void Util::create_name_log_file(std::string new_name) {
	Util::name_log_file = new_name;
}