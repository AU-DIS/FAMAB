cmake_minimum_required(VERSION 3.20)
project(efficient_multi_armed_bandits)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(csv-parser)
add_subdirectory(benchmark)

add_executable(efficient_multi_armed_bandits main.cpp
        algorithms/FPL/FPL.h
        algorithms/Exp3Bandit/Exp3VectorWeightStrategy.cpp utilities/weight_exporter.cpp
        datasets/dataloaders.h datasets/Dataset_movielens.h algorithms/Exp3Bandit/Exp3Bandit.h
        algorithms/Exp3Bandit/Exp3RewardStrategy.h algorithms/Exp3Bandit/Exp3VectorWeightStrategy.h
        datasets/debug/debug_simple_stochastic.cpp datasets/debug/debug_simple_stochastic.h datasets/debug/debug_simple_adversarial.cpp
        datasets/debug/debug_simple_adversarial.h algorithms/DEXP/DExp3.cpp algorithms/DEXP/DExp3.h algorithms/Exp3m/Exp3m.h
        utilities/argsort.h algorithms/Exp3Bandit/Exp31.h algorithms/FPL/NaiveRandomGenStrategy.cpp algorithms/FPL/NaiveRandomGenStrategy.h
        algorithms/FPL/FPLVectorWeightStrategy.cpp algorithms/FPL/FPLVectorWeightStrategy.h algorithms/Exp3m/DepRoundALIASStrategy.cpp
        algorithms/Exp3m/DepRoundALIASStrategy.h algorithms/Exp3m/Exp31m.h algorithms/Tsallis-INF/TsallisINF.h
        algorithms/UCB/UCB1.h algorithms/RBA/RBA.h algorithms/RBA/IBA.h utilities/random_gen.h utilities/exec_command.h runner.h utilities/result_writer.h
        datasets/dataset_simple_stochastic.h experiments/GenericBanditRunner.h datasets/dataset_simple_adversarial.h algorithms/Uniformbandit.h)

add_executable(benchmark_bandits benchmark.cpp
        algorithms/FPL/FPL.h
        algorithms/Exp3Bandit/Exp3VectorWeightStrategy.cpp utilities/weight_exporter.cpp
        datasets/dataloaders.h datasets/Dataset_movielens.h algorithms/Exp3Bandit/Exp3Bandit.h
        algorithms/Exp3Bandit/Exp3RewardStrategy.h algorithms/Exp3Bandit/Exp3VectorWeightStrategy.h
        datasets/debug/debug_simple_stochastic.cpp datasets/debug/debug_simple_stochastic.h datasets/debug/debug_simple_adversarial.cpp
        datasets/debug/debug_simple_adversarial.h algorithms/DEXP/DExp3.cpp algorithms/DEXP/DExp3.h algorithms/Exp3m/Exp3m.h
        utilities/argsort.h algorithms/Exp3Bandit/Exp31.h algorithms/FPL/NaiveRandomGenStrategy.cpp algorithms/FPL/NaiveRandomGenStrategy.h
        algorithms/FPL/FPLVectorWeightStrategy.cpp algorithms/FPL/FPLVectorWeightStrategy.h algorithms/Exp3m/DepRoundALIASStrategy.cpp
        algorithms/Exp3m/DepRoundALIASStrategy.h algorithms/Exp3m/Exp31m.h algorithms/Tsallis-INF/TsallisINF.h
        algorithms/UCB/UCB1.h algorithms/RBA/RBA.h algorithms/RBA/IBA.h utilities/random_gen.h utilities/exec_command.h runner.h utilities/result_writer.h
        datasets/dataset_simple_stochastic.h experiments/GenericBanditRunner.h datasets/dataset_simple_adversarial.h algorithms/Uniformbandit.h algorithms/Tsallis-INF/TsallisIW.h algorithms/Tsallis-INF/TsallisRV.h experiments/TsallisExperimentRunner.h)

target_link_libraries(efficient_multi_armed_bandits csv)
target_link_libraries(benchmark_bandits benchmark::benchmark)