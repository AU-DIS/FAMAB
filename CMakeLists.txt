cmake_minimum_required(VERSION 3.20)
project(efficient_multi_armed_bandits)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(csv-parser)
add_subdirectory(benchmark)

add_executable(efficient_multi_armed_bandits main.cpp
        algorithms/FPL/FPL.h
        utilities/weight_exporter.cpp
        datasets/dataset_theoretical_bounds.h datasets/dataloaders.h datasets/Dataset_movielens.h algorithms/Exp3Bandit/Exp3.h
        datasets/debug/debug_simple_stochastic.cpp datasets/debug/debug_simple_stochastic.h datasets/debug/debug_simple_adversarial.cpp
        datasets/debug/debug_simple_adversarial.h algorithms/DEXP/DExp3.cpp algorithms/DEXP/DExp3.h algorithms/Exp3m/Exp3m.h
        utilities/argsort.h algorithms/FPL/NaiveRandomGenStrategy.cpp algorithms/FPL/NaiveRandomGenStrategy.h
        algorithms/FPL/FPLVectorWeightStrategy.cpp algorithms/FPL/FPLVectorWeightStrategy.h algorithms/Exp3m/DepRoundALIASStrategy.cpp
        algorithms/Exp3m/DepRoundALIASStrategy.h algorithms/Exp3m/Exp31m.h algorithms/Tsallis-INF/TsallisINF.h
        algorithms/Exp3Bandit/Exp3.h algorithms/Exp3Bandit/Exp3.cpp
        algorithms/Exp3Bandit/Exp31.h algorithms/Exp3Bandit/Exp31.cpp
        algorithms/Exp3Bandit/Exp3Tor.h algorithms/Exp3Bandit/Exp3Tor.cpp
        algorithms/Exp3Bandit/Exp3IXTor.h algorithms/Exp3Bandit/Exp3IXTor.cpp
        algorithms/UCB/UCB1.h algorithms/RBA/RBA.h algorithms/RBA/IBA.h utilities/random_gen.h utilities/exec_command.h runner.h utilities/result_writer.h
        datasets/dataset_simple_stochastic.h experiments/TheoreticalBoundRunner.h experiments/GenericBanditRunner.h datasets/dataset_simple_adversarial.h algorithms/Uniformbandit.h)

add_executable(benchmark_bandits benchmark.cpp
        algorithms/FPL/FPL.h
        utilities/weight_exporter.cpp
        datasets/dataloaders.h datasets/Dataset_movielens.h algorithms/Exp3Bandit/Exp3.h
        datasets/debug/debug_simple_stochastic.cpp datasets/debug/debug_simple_stochastic.h datasets/debug/debug_simple_adversarial.cpp
        datasets/debug/debug_simple_adversarial.h algorithms/DEXP/DExp3.cpp algorithms/DEXP/DExp3.h algorithms/Exp3m/Exp3m.h
        utilities/argsort.h algorithms/FPL/NaiveRandomGenStrategy.cpp algorithms/FPL/NaiveRandomGenStrategy.h
        algorithms/FPL/FPLVectorWeightStrategy.cpp algorithms/FPL/FPLVectorWeightStrategy.h algorithms/Exp3m/DepRoundALIASStrategy.cpp
        algorithms/Exp3m/DepRoundALIASStrategy.h algorithms/Exp3m/Exp31m.h algorithms/Tsallis-INF/TsallisINF.h
        algorithms/Exp3Bandit/Exp3.h algorithms/Exp3Bandit/Exp3.cpp
        algorithms/Exp3Bandit/Exp31.h algorithms/Exp3Bandit/Exp31.cpp
        algorithms/Exp3Bandit/Exp3Tor.h algorithms/Exp3Bandit/Exp3Tor.cpp
        algorithms/Exp3Bandit/Exp3IXTor.h algorithms/Exp3Bandit/Exp3IXTor.cpp
        experiments/TheoreticalBoundRunner.h
        algorithms/UCB/UCB1.h algorithms/RBA/RBA.h algorithms/RBA/IBA.h utilities/random_gen.h utilities/exec_command.h runner.h utilities/result_writer.h
        datasets/dataset_simple_stochastic.h experiments/GenericBanditRunner.h datasets/dataset_simple_adversarial.h algorithms/Uniformbandit.h algorithms/FPL/FPL_hash.h experiments/FPLComparisonRunner.h datasets/data_generators.h utilities/updateable_priority_queue.h algorithms/FPL/QBL.h experiments/TsallisComparisonRunner.h algorithms/Tsallis-INF/Tsallis_IW.h algorithms/Tsallis-INF/Tsallis_RV.h)

target_link_libraries(efficient_multi_armed_bandits csv)
target_link_libraries(benchmark_bandits benchmark::benchmark)