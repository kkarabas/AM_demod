cmake_minimum_required(VERSION 3.0)

project(am_demod VERSION 1.0.0 LANGUAGES CXX)

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}  PUBLIC "${PROJECT_SOURCE_DIR}/headers")

add_subdirectory(${PROJECT_SOURCE_DIR}/filter)
add_subdirectory(${PROJECT_SOURCE_DIR}/wav)
add_subdirectory(${PROJECT_SOURCE_DIR}/am_mod)

target_link_libraries(${PROJECT_NAME} am_demod_filter)
target_link_libraries(${PROJECT_NAME} am_demod_wav)
target_link_libraries(${PROJECT_NAME} am_demod_mod)

#install(TARGETS am_demod DESTINATION "${PROJECT_SOURCE_DIR}/bin")

################################
# Testing
################################
find_package(GTest REQUIRED)
enable_testing()

if (${GTest_FOUND})
	include_directories(${GTEST_INCLUDE_DIRS})

	set(SOURCE_FILES test.cpp)
	add_executable(runTests ${SOURCE_FILES})

	target_link_libraries(runTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
	
	target_include_directories(runTests PUBLIC "${PROJECT_SOURCE_DIR}/headers")	
	target_link_libraries(runTests am_demod_filter)
	target_link_libraries(runTests am_demod_wav)
	target_link_libraries(runTests am_demod_mod)

	add_test(test runTests)
	
endif()	

#include(GoogleTest)
#gtest_discover_tests(runTests)
