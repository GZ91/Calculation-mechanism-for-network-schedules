
cmake_minimum_required (VERSION 3.8)


project (NC_Develop)

find_package(nlohmann_json)

add_executable(NC_Develop "main.cpp" "schedule.hpp" "schedule.cpp" "schedule_util.cpp" "schedule_task.cpp") 

target_include_directories(
    NC_Develop PRIVATE
	${NLOHMANNDIR}
)


set_target_properties(NC_Develop PROPERTIES
	CMAKE_CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)


