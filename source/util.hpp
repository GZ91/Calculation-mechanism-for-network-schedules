#pragma once
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
//#include <ctime>
#include "nlohmann\json.hpp"


using json = nlohmann::json;

class Util {
public:
	static std::tm dt_from_str(std::string);
	static std::tm dt_from_json(json);
	static std::chrono::milliseconds time_measurement(void (*method)());
	static void write_in_log(std::string, int type_error = 0);
	static void create_name_log_file(std::string);
	static std::string name_log_file;
};