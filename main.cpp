#include <iostream>
#include "algorithms/Exp3.h"
#include "experiments/fpl/fpl_mod2.cpp"
#include "experiments/exp3/exp3_mod2.cpp"
#include <benchmark/benchmark.h>


int main() {
    int K = 1000;
    int iterations = 90000;
    run_fpl_mod2_bandit(1, K, iterations);
    std::cout << "\n";
    run_exp3_mod2_bandit(0.1, K, iterations);
}
