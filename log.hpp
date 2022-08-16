#pragma once
#include <fstream>
#include <string>
#include <ctime>

void write_in_log(std::string text_log, int type_error = 0) {
	std::fstream log_f("log.txt", std::ios::app);
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds); 
	std::string end = "";
	if (type_error != 0) {
		end = " @program crash@";
	}
	log_f << end << text_log << " % " << asctime(timeinfo);
	if (type_error != 0) {
		exit(type_error);
	}
}

