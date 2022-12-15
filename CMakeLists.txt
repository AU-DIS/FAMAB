cmake_minimum_required(VERSION 3.20)
project(efficient_multi_armed_bandits)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(csv-parser)
add_subdirectory(benchmark)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})


SET(DBENCHMARK_ENABLE_GTEST_TESTS OFF)

add_executable(efficient_multi_armed_bandits main.cpp
        algorithms/Exp3m/Exp3m.h
        algorithms/Exp3m/DepRoundALIASStrategy.cpp
        algorithms/Exp3m/DepRoundALIASStrategy.h
        algorithms/Exp3Bandit/Exp3.h
        algorithms/Exp3Bandit/Exp3.cpp
        algorithms/Exp3Bandit/Exp31.h
        algorithms/Exp3Bandit/Exp31.cpp
        algorithms/Exp3Bandit/Exp3Tor.h algorithms/Exp3Bandit/Exp3Tor.cpp
        algorithms/Exp3Bandit/Exp3IXTor.h algorithms/Exp3Bandit/Exp3IXTor.cpp
        algorithms/Exp3Bandit/exp3r.h)


        
add_executable(benchmark_bandits benchmark.cpp
        algorithms/Exp3m/Exp3m.h
        algorithms/Exp3m/DepRoundALIASStrategy.cpp
        algorithms/Exp3m/DepRoundALIASStrategy.h
        algorithms/Exp3Bandit/Exp3.h
        algorithms/Exp3Bandit/Exp3.cpp
        algorithms/Exp3Bandit/Exp31.h
        algorithms/Exp3Bandit/Exp31.cpp
        algorithms/Exp3Bandit/Exp3Tor.h algorithms/Exp3Bandit/Exp3Tor.cpp
        algorithms/Exp3Bandit/Exp3IXTor.h algorithms/Exp3Bandit/Exp3IXTor.cpp
        algorithms/Exp3m/Exp3m_heap.h algorithms/Exp3m/Exp31m_2.h algorithms/Exp3Bandit/exp3r.h datastructures/Incremental_sum_heap.h datastructures/Incremental_product_heap.h)

add_executable(optimal_parameter_finder optimal_parameter_finder.cpp
algorithms/Exp3Bandit/Exp3.h
algorithms/Exp3Bandit/Exp3.cpp
)

add_executable(duelling_bandits duelling_bandits.cpp
algorithms/Exp3Bandit/Exp3.h
algorithms/Exp3Bandit/Exp3.cpp
)

target_link_libraries(efficient_multi_armed_bandits csv Boost::boost)
target_link_libraries(benchmark_bandits benchmark::benchmark)