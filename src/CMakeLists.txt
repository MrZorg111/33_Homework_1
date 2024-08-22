cmake_minimum_required (VERSION 3.21)

add_executable("33_Homework_1" main.cpp ${MY_INCLUDE_DIR}/market.h ${MY_INCLUDE_DIR}/basket.h)
target_include_directories("33_Homework_1" PUBLIC ${MY_INCLUDE_DIR})
target_link_libraries("33_Homework_1" PRIVATE nlohmann_json::nlohmann_json)