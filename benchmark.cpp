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

static void benchmark_exp3m_10_sample(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    std::vector<double> reward(10);
    std::vector<int> index(10);
    for (auto _ : state) {
        DepRoundALIASStrategy a;
        Exp3m b(k, 1, 0.1, a);
        for (int i = 0; i < rounds; i++) {
            auto choices = b.choose();
        }
    }
}

static void benchmark_exp3m_10_update(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 1000;
    std::vector<double> reward;
    std::vector<int> index;
    for (int i = 0; i < k; i++) {
        reward.push_back(i);
        index.push_back(i);
    }

    for (auto _ : state) {
        DepRoundALIASStrategy a;
        Exp3m b(k, 1, 0.1, a);
        auto choices = b.choose();
        for (int i = 0; i < rounds; i++) {
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
        Exp3 bandit(k, 0.1);
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

static void benchmark_fpl_sample(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        int rounds = 1000;
        FPLVectorWeightStrategy ws(k);
        NaiveRandomGenStrategy gs(k, 0.1);
        FPL b(ws, gs);
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_fpl_update(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        int rounds = 1000;
        FPLVectorWeightStrategy ws(k);
        NaiveRandomGenStrategy gs(k, 0.1);
        FPL b(ws, gs);
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}


static void benchmark_exp31(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp31 b(k);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp31_sample(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp31 b(k);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp31_update(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp31 b(k);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3 b(k, 0.1);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3_sample(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3 b(k, 0.1);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3_update(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3 b(k, 0.1);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_exp3eta(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3Tor b(k, 0.1);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3eta_sample(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3Tor b(k, 0.1);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3eta_update(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        Exp3Tor b(k, 0.1);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
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

static void benchmark_tsallis_sample(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        TsallisIW iw;
        TsallisINF b(k, iw);
        int rounds = 1000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_tsallis_update(benchmark::State& state) {
    auto k = state.range(0);
    for (auto _ : state) {
        TsallisIW iw;
        TsallisINF b(k, iw);
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


BENCHMARK(benchmark_exp3m_10)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);



BENCHMARK(benchmark_exp3m_10_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3m_10_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
*/
BENCHMARK(benchmark_exp3eta)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3eta_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);
BENCHMARK(benchmark_exp3eta_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000)->Threads(15);

BENCHMARK_MAIN();