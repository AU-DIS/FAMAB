//
// Created by Mathias Tversted on 05/02/2022.
//

#include <iostream>
#include "../../algorithms/FPL.h"
#include "benchmark/benchmark.h"
#include "../../benchmark_variables.h"



static void run_fpl_mod2_bandit(double eta, int K, int iterations) {
    FPL bandit = FPL(eta, K);
    srand(time(NULL));
    int no_correct = 0;
    int no_wrong = 0;
    for (int i = 0; i < iterations; i++) {
        int c = bandit.draw();
        if (c % 2 == 0) {
            no_correct ++;
            bandit.give_reward(c, 1);
        }
        else {
            no_wrong ++;
            bandit.give_reward(c, 0);
        }
    }
    
}

static void BM_FPL(benchmark::State& state) {
    for (auto _ : state) {
        // This code gets timed
        run_fpl_mod2_bandit(BENCHMARK_ETA, BENCHMARK_K, BENCHMARK_ITERATIONS);
    }

}

