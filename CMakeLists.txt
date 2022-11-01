cmake_minimum_required(VERSION 3.22.1)

project(Logger)

include_directories(inc)
add_library(logger INTERFACE inc)

add_executable(test src/main.cpp)
target_link_libraries(test logger)