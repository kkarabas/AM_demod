cmake_minimum_required(VERSION 3.0)

project(am_demod VERSION 1.0.0 LANGUAGES CXX)

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}  PUBLIC "${PROJECT_SOURCE_DIR}/headers")

add_subdirectory(${PROJECT_SOURCE_DIR}/filter)
add_subdirectory(${PROJECT_SOURCE_DIR}/wav)

target_link_libraries(${PROJECT_NAME} am_demod_filter)
target_link_libraries(${PROJECT_NAME} am_demod_wav)

#install(TARGETS am_demod DESTINATION "${PROJECT_SOURCE_DIR}/bin")
