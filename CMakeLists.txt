cmake_minimum_required(VERSION 3.0)

project(wave-equation)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(wave-equation src/main.cpp src/simulation.cpp src/settings.cpp)
