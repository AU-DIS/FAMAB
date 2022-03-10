//
// Created by Mathias Ravn Tversted on 10/03/2022.
//
#include "iostream"
#include <benchmark/benchmark.h>
#include "random"
#include "algorithms/FPL/FPLVectorWeightStrategy.h"
#include "algorithms/FPL/NaiveRandomGenStrategy.h"
#include "algorithms/FPL/FPL.h"
#include "algorithms/Exp3Bandit/Exp3VectorWeightStrategy.h"
#include "algorithms/Exp3Bandit/Exp3RewardStrategy.h"
#include "algorithms/Exp3Bandit/Exp31.h"
#include "algorithms/Exp3Bandit/Exp3Bandit.h"
#include "algorithms/Tsallis-INF/TsallisINF.h"

static void benchmark_fpl(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        int rounds = 1000;
        FPLVectorWeightStrategy ws(k);
        NaiveRandomGenStrategy gs(k, 0.1);
        FPL b(ws, gs);
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_exp31(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3VectorWeightStrategy ws31(k, 0.1);
        Exp3RewardStrategy rs31(ws31);
        Exp31 b(ws31, rs31);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_exp3(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3VectorWeightStrategy ws(k, 0.1);
        Exp3RewardStrategy rs(ws);
        Exp3Bandit b(ws, rs);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_tsallis(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        TsallisINF b(k);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}


BENCHMARK(benchmark_fpl)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_exp31)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_exp3)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_tsallis)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK_MAIN();