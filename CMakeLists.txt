
cmake_minimum_required (VERSION 3.8)


project (VC_Develop)

find_package(nlohmann_json)

add_executable(VC_Develop "main.cpp")

target_include_directories(
    VC_Develop PRIVATE
	${NLOHMANNDIR}
    #"C:\\my\\library\\nlohmann\\include"
)
# Add googletest to the include directories for the test target
#target_include_directories(
#    VC_Develop PRIVATE
#    "C:\\my\\library\\nlohmann\\"
#)

# Link test target against gtest libraries
#target_link_libraries(
#    VC_Develop PRIVATE
#    "C:\\my\\library\\nlohmann"
#)



set_target_properties(VC_Develop PROPERTIES
	CMAKE_CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)


