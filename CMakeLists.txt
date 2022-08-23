
cmake_minimum_required (VERSION 3.8)


project (NC_Develop)
project (NC_Develop_Testing)


# Download and build googletest
# @see https://github.com/google/googletest/blob/master/googletest/README.md
# Incorporating Into An Existing CMake Project

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)
# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

find_package(nlohmann_json)

add_executable(NC_Develop "main.cpp" "schedule.hpp" "schedule.cpp" "schedule_util.cpp" "schedule_task.cpp") 




add_executable(NC_Develop_Testing "schedule.hpp" "schedule.cpp" "schedule_util.cpp" "schedule_task.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp") 


target_link_libraries(
	NC_Develop_Testing PRIVATE
	gtest gtest_main
)

target_include_directories(
    NC_Develop PRIVATE
	${NLOHMANNDIR}
)

target_include_directories(
    NC_Develop_Testing PRIVATE
	${NLOHMANNDIR}
)


set_target_properties(NC_Develop PROPERTIES
	CMAKE_CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

set_target_properties(NC_Develop_Testing PROPERTIES
	CMAKE_CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)


