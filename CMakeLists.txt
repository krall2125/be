cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

project(be VERSION 1.0)

add_executable(be src/main.c)

target_include_directories(be PRIVATE ./include/)
