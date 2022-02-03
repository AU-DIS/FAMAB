cmake_minimum_required(VERSION 3.20)
project(efficient_multi_armed_bandits)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)

add_executable(efficient_multi_armed_bandits main.cpp algorithms/Exp3.cpp algorithms/Exp3.h experiments/exp3/mod2.cpp)
target_link_libraries(efficient_multi_armed_bandits benchmark::benchmark)