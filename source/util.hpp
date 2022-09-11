#pragma once
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
//#include <ctime>
#include "nlohmann\json.hpp"


using json = nlohmann::json;

namespace Util{

	std::tm dt_from_str(std::string); //конвертировать строку в tm
	std::tm dt_from_json(json); //конвертировать json в tm
	std::time_t time_t_from_json(json); //конвертироваться json в time_t
	std::chrono::milliseconds time_measurement(void (*method)()); //вычисляет время выполнения процедуры
	void write_in_log(std::string, int type_error = 0); //записать в лог
	void create_name_log_file(std::string); // присвоить имя файла логу
	static std::string name_log_file; // имя файла логирования
};