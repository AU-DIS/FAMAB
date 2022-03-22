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
#include "algorithms/Exp3Bandit/Exp3.h"
#include "algorithms/Tsallis-INF/TsallisINF.h"
#include "algorithms/Tsallis-INF/TsallisRV.h"
#include "algorithms/Tsallis-INF/TsallisIW.h"
#include "algorithms/DEXP/DExp3.h"
#include "algorithms/Exp3m/DepRoundALIASStrategy.h"
#include "algorithms/Exp3m/Exp3m.h"
#include "algorithms/Exp3m/Exp31m.h"
#include "algorithms/UCB/UCB1.h"


static void benchmark_dexp(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    for (auto _ : state) {
        DExp3 b(k, 0.1, 0.1);
        for (int i = 0; i < rounds; i++) {
            auto [choice1, choice2]= b.choose();
            b.give_reward(0, 0, 1, i);
        }
    }
}

static void benchmark_exp3m_10(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    std::vector<double> reward(10);
    std::vector<int> index(10);
    for (auto _ : state) {
        DepRoundALIASStrategy a;
        Exp3m b(k, 1, 0.1, a);
        for (int i = 0; i < rounds; i++) {
            auto choices = b.choose();
            b.give_reward(index, reward);
        }
    }
}
static void benchmark_exp31m_10(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    std::vector<double> reward(10);
    std::vector<int> index(10);
    for (auto _ : state) {
        DepRoundALIASStrategy a;
        Exp3m bandit(k, 1, 0.1, a);
        Exp31m b(k, 1, bandit);
        for (int i = 0; i < rounds; i++) {
            auto choices = b.choose();
            b.give_reward(index, reward);
        }
    }
}


static void benchmark_ucb_fpl(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        int rounds = 1000;
        FPLVectorWeightStrategy ws(k);
        NaiveRandomGenStrategy gs(k, 0.1);
        FPL bandit(ws, gs);
        UCB1 b(10, bandit);
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_ucb_exp3(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3VectorWeightStrategy ws(k, 0.1);
        Exp3RewardStrategy rs(ws);
        Exp3Bandit bandit(ws, rs);
        UCB1 b(10, bandit);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}



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
static void benchmark_tsallis_rv(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        TsallisRV rv;
        TsallisINF b(k, rv);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_tsallis_iw(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        TsallisIW iw;
        TsallisINF b(k, iw);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}


/*
BENCHMARK(benchmark_fpl)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_exp31)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_exp3)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
*/
/*
BENCHMARK(benchmark_tsallis_rv)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_tsallis_iw)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
 BENCHMARK(benchmark_dexp)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
 */
BENCHMARK(benchmark_ucb_exp3)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_ucb_fpl)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_exp31m_10)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);
BENCHMARK(benchmark_exp3m_10)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Arg(10000000)->Threads(15);

BENCHMARK_MAIN();