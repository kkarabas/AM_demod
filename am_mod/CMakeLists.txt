cmake_minimum_required(VERSION 3.0)

project(am_demod_mod VERSION 1.0.0 LANGUAGES CXX)

set(SOURCE_FILES am_mod.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ../headers)
