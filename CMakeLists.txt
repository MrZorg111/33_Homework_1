cmake_minimum_required(VERSION 3.21)
project("33_Homework_1" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(JSON BuildTest OFF CACHE INTERNAL "")

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(nlohmann_json)