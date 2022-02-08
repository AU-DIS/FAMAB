//
// Created by Mathias Ravn Tversted on 03/02/2022.
//
#include <iostream>
#include "../../benchmark_variables.h"
#include "../../algorithms/VectorWeightStrategy.cpp"
#include "../../algorithms/Exp3RewardStrategy.cpp"
#include "../../algorithms/Exp3Bandit.cpp"
#include <benchmark/benchmark.h>

static void run_exp3_mod2_bandit(double gamma, int k, int iterations) {
    auto vws = VectorWeightStrategy(k, gamma);
    auto exp3rs = Exp3RewardStrategy(&vws);
    Exp3Bandit bandit = Exp3Bandit(&vws, &exp3rs);
    int no_correct = 0;
    int no_wrong = 0;
    for (int i = 0; i < iterations; i++) {
        int c = bandit.choose();
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
static void BM_Exp3(benchmark::State& state) {
    for (auto _ : state) {
        // This code gets timed
        run_exp3_mod2_bandit(BENCHMARK_GAMMA, BENCHMARK_K, BENCHMARK_ITERATIONS);
    }
}

