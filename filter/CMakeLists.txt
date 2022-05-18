cmake_minimum_required(VERSION 3.0)

project(am_demod_filter VERSION 1.0.0 LANGUAGES CXX)

set(SOURCE_FILES filter.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ../headers)
