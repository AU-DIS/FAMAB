cmake_minimum_required(VERSION 3.20)
project(efficient_multi_armed_bandits)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(benchmark)
add_subdirectory(csv-parser)

add_executable(efficient_multi_armed_bandits main.cpp
        algorithms/FPL.cpp
        algorithms/FPL.h
        benchmark_variables.h
        algorithms/VectorWeightStrategy.cpp  utilities/weight_exporter.cpp
        datasets/IDataset.h datasets/dataloaders.cpp datasets/Dataset_movielens.h datasets/Dataset_movielens.cpp algorithms/Exp3Bandit.h algorithms/Exp3RewardStrategy.h algorithms/VectorWeightStrategy.h)
target_link_libraries(efficient_multi_armed_bandits benchmark::benchmark)
target_link_libraries(efficient_multi_armed_bandits csv)
