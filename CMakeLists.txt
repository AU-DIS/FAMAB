cmake_minimum_required(VERSION 3.20)
project(efficient_multi_armed_bandits)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(benchmark)
add_subdirectory(csv-parser)

add_executable(efficient_multi_armed_bandits main.cpp
        algorithms/FPL/FPL.h
        benchmark_variables.h
        algorithms/Exp3Bandit/VectorWeightStrategy.cpp utilities/weight_exporter.cpp
        datasets/dataloaders.cpp datasets/Dataset_movielens.h datasets/Dataset_movielens.cpp algorithms/Exp3Bandit/Exp3Bandit.h algorithms/Exp3Bandit/Exp3RewardStrategy.h algorithms/Exp3Bandit/VectorWeightStrategy.h datasets/debug_simple_stochastic.cpp datasets/debug_simple_stochastic.h datasets/debug_simple_adversarial.cpp datasets/debug_simple_adversarial.h algorithms/DExp3.cpp algorithms/DExp3.h algorithms/Exp3m.cpp algorithms/Exp3m.h utilities/argsort.cpp algorithms/FPL/NaiveRandomGenStrategy.cpp algorithms/FPL/NaiveRandomGenStrategy.h algorithms/FPL/VectorWeightStrategy.cpp algorithms/FPL/VectorWeightStrategy.h)
target_link_libraries(efficient_multi_armed_bandits benchmark::benchmark)
target_link_libraries(efficient_multi_armed_bandits csv)
