#pragma once
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
//#include <ctime>
#include "nlohmann\json.hpp"


using json = nlohmann::json;

namespace Util{

	std::tm dt_from_str(std::string);
	std::tm dt_from_json(json);
	std::time_t time_t_from_json(json);
	std::chrono::milliseconds time_measurement(void (*method)());
	void write_in_log(std::string, int type_error = 0);
	void create_name_log_file(std::string);
	static std::string name_log_file;
};