
#pragma once
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>

#include "nlohmann\json.hpp"
using json = nlohmann::json;

namespace util {
	void detect_type_val(json active) {
		bool do_write = true;
		if (active.is_null()) {
			std::cout << "NULL!!!" << std::endl;
			do_write = false;
		}
		else if (active.is_number())
			std::cout << "NUMBER!!!" << std::endl;
		else if (active.is_string())
			std::cout << "STRING!!!" << std::endl;
		else if (active.is_boolean())
			std::cout << "BOOLEAN!!!" << std::endl;
		else if (active.is_number_integer())
			std::cout << "NUMBER_INT!!!" << std::endl;
		else if (active.is_number_unsigned())
			std::cout << "NUMBER_UNS!!!" << std::endl;
		else if (active.is_number_float())
			std::cout << "NUMBER_FLT!!!" << std::endl;
		else if (active.is_binary())
			std::cout << "BINARY!!!" << std::endl;
		else if (active.is_discarded())
			std::cout << "DISCARDED!!!" << std::endl;
		else if (active.is_primitive())
			std::cout << "PRIMITIVE!!!" << std::endl;
		else std::cout << "I DON'T KNOW!!!!" << std::endl;
		if (do_write)
			std::cout << active << std::endl;
	}

	std::tm dt_from_str(std::string str)
	{
		std::wstring wstr_date_plan(str.begin(), str.end());
		static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
		std::wistringstream ss{ wstr_date_plan };
		std::tm dt;
		ss >> std::get_time(&dt, dateTimeFormat.c_str());
		return dt;
	}



	std::chrono::milliseconds time_measurement(void (*method)()) {
		auto start = std::chrono::high_resolution_clock::now();
		method();
		auto end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	}
}