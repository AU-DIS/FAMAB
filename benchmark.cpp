//
// Created by Mathias Ravn Tversted on 10/03/2022.
//
#include "iostream"
#include <benchmark/benchmark.h>
#include "random"
#include "algorithms/FPL/FPLVectorWeightStrategy.h"
#include "algorithms/FPL/NaiveRandomGenStrategy.h"
#include "algorithms/FPL/FPL.h"
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
#include "algorithms/Exp3Bandit/Exp3Tor.h"


static void benchmark_exp3m_1(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    int K = 1;
    std::vector<double> reward(K, 1);
    std::vector<int> index(K, 1);
    DepRoundALIASStrategy a;
    Exp3m b(k, K, 0.1, a);

    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            auto choices = b.choose();
            b.give_reward(index, reward);
        }
    }
}

static void benchmark_exp3m_1_sample(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    int K = 1;
    std::vector<double> reward(K, 1);
    std::vector<int> index(K, 1);
    DepRoundALIASStrategy a;
    Exp3m b(k, K, 0.1, a);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            auto choices = b.choose();
        }
    }
}

static void benchmark_exp3m_1_update(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    int K = 1;
    std::vector<double> reward(K, 0);
    std::vector<int> index(K, 0);
    DepRoundALIASStrategy a;
    Exp3m b(k, K, 0.1, a);
    b.choose();
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            b.give_reward(index, reward);
        }
    }
}

static void benchmark_ucb_fpl(benchmark::State& state) {
    auto k = state.range(0);
    FPLVectorWeightStrategy ws(k);
    NaiveRandomGenStrategy gs(k, 0.1);
    FPL bandit(ws, gs);
    UCB1 b(10, bandit);
    for (auto _ : state) {
        int rounds = 1000;

        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_ucb_exp3(benchmark::State& state) {
    auto k = state.range(0);
    Exp3 bandit(k, 0.1);
    UCB1 b(10, bandit);
    for (auto _ : state) {

        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}



static void benchmark_fpl(benchmark::State& state) {
    auto k = state.range(0);
    FPLVectorWeightStrategy ws(k);
    NaiveRandomGenStrategy gs(k, 0.1);
    FPL b(ws, gs);
    for (auto _ : state) {
        int rounds = 1000;

        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_fpl_sample(benchmark::State& state) {
    auto k = state.range(0);
    FPLVectorWeightStrategy ws(k);
    NaiveRandomGenStrategy gs(k, 0.1);
    FPL b(ws, gs);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_fpl_update(benchmark::State& state) {
    auto k = state.range(0);
    FPLVectorWeightStrategy ws(k);
    NaiveRandomGenStrategy gs(k, 0.1);
    FPL b(ws, gs);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}


static void benchmark_exp31(benchmark::State& state) {
    auto k = state.range(0);
    Exp31 b(k);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp31_sample(benchmark::State& state) {
    auto k = state.range(0);
    Exp31 b(k);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp31_update(benchmark::State& state) {
    auto k = state.range(0);
    Exp31 b(k);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3(benchmark::State& state) {
    auto k = state.range(0);
    Exp3 b(k, 0.1);
    for (auto _ : state) {

        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3_sample(benchmark::State& state) {
    auto k = state.range(0);
    Exp3 b(k, 0.1);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3_update(benchmark::State& state) {
    auto k = state.range(0);
    Exp3 b(k, 0.1);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_exp3eta(benchmark::State& state) {
    auto k = state.range(0);
    Exp3Tor b(k, 0.1);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3eta_sample(benchmark::State& state) {
    auto k = state.range(0);
    Exp3Tor b(k, 0.1);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3eta_update(benchmark::State& state) {
    auto k = state.range(0);
    Exp3Tor b(k, 0.1);
    for (auto _ : state) {

        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_tsallis_rv(benchmark::State& state) {
    auto k = state.range(0);
    TsallisRV rv;
    TsallisINF b(k, rv);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_tsallis_iw(benchmark::State& state) {
    auto k = state.range(0);
    TsallisIW iw;
    TsallisINF b(k, iw);
    for (auto _ : state) {
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_tsallis_sample(benchmark::State& state) {
    auto k = state.range(0);
    TsallisIW iw;
    TsallisINF b(k, iw);
    for (auto _ : state) {

        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_tsallis_update(benchmark::State& state) {
    auto k = state.range(0);
    TsallisIW iw;
    TsallisINF b(k, iw);
    for (auto _ : state) {

        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}


/*
BENCHMARK(benchmark_fpl)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_fpl_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_fpl_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);

BENCHMARK(benchmark_exp31)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp31_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp31_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);

BENCHMARK(benchmark_exp3)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);

BENCHMARK(benchmark_tsallis_rv)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_tsallis_iw)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_tsallis_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_tsallis_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);

BENCHMARK(benchmark_ucb_exp3)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_ucb_fpl)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);


BENCHMARK(benchmark_exp3m_1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3m_1_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
 */
BENCHMARK(benchmark_exp3m_1_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
/*

BENCHMARK(benchmark_exp3eta)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3eta_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3eta_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
*/
BENCHMARK_MAIN();