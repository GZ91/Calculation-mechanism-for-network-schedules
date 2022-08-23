#include "gtest/gtest.h"
#include "../source/schedule.hpp"




TEST(Schedule, Exist_To_File_Log) {
	//std::ifstream f("..\\..\\..\\resource_big.json");
	std::ifstream f("..\\..\\..\\resource.json");
	if (f.fail()) ASSERT_TRUE(false);
	json data = json::parse(f);
	f.close();
	Schedule sch(data, "logovo.txt");
	Schedule::Util::write_in_log("test");
   
    std::ifstream file;
    file.open("logovo.txt");
    file.close();
    ASSERT_TRUE(file ? true : false); // file exist?
}


TEST(Schedule, dt_from_str) {
	std::string date = "2020-07-03T00:00:00";
	tm dt_1 = Schedule::Util::dt_from_str(date);
	
	time_t seconds_1 = std::mktime(&dt_1);


	tm dt_2{};
	dt_2.tm_year = 120; //[1900 - ..] 2020 = 120
	dt_2.tm_mon = 6;	//[0 - 11]
	dt_2.tm_mday = 3;	//[1 - 31]
	time_t seconds_2 = std::mktime(&dt_2);
	ASSERT_EQ(seconds_1, seconds_2);
}

TEST(Schedule, processed_against_a_benchmark) {
	std::ifstream f("..\\..\\..\\resource.json");
	if (f.fail()) ASSERT_TRUE(false);
	json data = json::parse(f);
	f.close();
	Schedule sch(data, "logovo.txt");
	
}