//
// Created by Mathias Ravn Tversted on 1/03/2022.
//
#include "iostream"
#include <benchmark/benchmark.h>
#include "random"
#include "algorithms/FPL/FPLVectorWeightStrategy.h"
#include "algorithms/FPL/NaiveRandomGenStrategy.h"
#include "algorithms/FPL/FPL.h"
#include "algorithms/FPL/FPL_hash.h"
#include "algorithms/Exp3Bandit/Exp31.h"
#include "algorithms/Exp3Bandit/Exp3.h"
#include "algorithms/Tsallis-INF/TsallisINF.h"
#include "algorithms/Tsallis-INF/RV.h"
#include "algorithms/Tsallis-INF/IW.h"
#include "algorithms/Tsallis-INF/Tsallis_RV.h"
#include "algorithms/Tsallis-INF/Tsallis_IW.h"
#include "algorithms/Tsallis-INF/Tsallis_optimized.h"
#include "algorithms/DEXP/DExp3.h"
#include "algorithms/Exp3m/DepRoundALIASStrategy.h"
#include "algorithms/Exp3m/Exp3m.h"
#include "algorithms/Exp3m/Exp31m.h"
#include "algorithms/UCB/UCB1.h"
#include "algorithms/Exp3Bandit/Exp3Tor.h"
#include "algorithms/Exp3Bandit/Exp3_heap.h"
#include "algorithms/Exp3Bandit/Exp3_deferred.h"
#include "algorithms/Exp3Bandit/Exp3_average.h"
#include "experiments/AdversarialExperimentRunner.h"
#include "datasets/data_generators.h"


static void benchmark_exp3m_1(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
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
    int rounds = 100;
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
    int rounds = 100;
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
    UCB1 b(1, bandit);
    for (auto _ : state) {
        int rounds = 100;

        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_ucb_exp3(benchmark::State& state) {
    auto k = state.range(0);
    Exp3 bandit(k, 0.1);
    UCB1 b(1, bandit);
    for (auto _ : state) {

        int rounds = 100;
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
        int rounds = 100;

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
        int rounds = 100;
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
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_qbl(benchmark::State& state) {
    auto k = state.range(0);
    QBL b(k, 0.1);
    for (auto _ : state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(i % k, 1);
        }
    }
}

static void benchmark_qbl_sample(benchmark::State& state) {
    auto k = state.range(0);
    QBL b(k, 0.1);
    for (auto _ : state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_qbl_update(benchmark::State& state) {
    auto k = state.range(0);
    QBL b(k, 0.1);
    for (auto _: state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(i % k, 1);
        }
    }
}


static void benchmark_fpl_hashing(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    FPL_hash b(k, 0.1, rounds);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_fpl_hashing_sample(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    FPL_hash b(k, 0.1, rounds);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_fpl_hashing_update(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    FPL_hash b(k, 0.1, rounds);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp31(benchmark::State& state) {
    auto k = state.range(0);
    Exp31 b(k);
    for (auto _ : state) {
        int rounds = 100;
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
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp31_update(benchmark::State& state) {
    auto k = state.range(0);
    Exp31 b(k);
    for (auto _ : state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3_defer(benchmark::State& state) {
    auto k = state.range(0);
    Exp3_deferred b(k, 0.1, 128);
    for (auto _ : state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}


static void benchmark_exp3_data(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    double gap = 3.2;
    double delta = 0.9;
    auto dataset = StochasticallyConstrainedDataset(k, rounds, gap, delta);
    auto d = dataset.generate();
    Exp3 b(k, 0.1);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(choice, d[choice][i]);
        }
    }
}

static void benchmark_exp3_average(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    double gap = 3.2;
    double delta = 0.9;
    auto dataset = StochasticallyConstrainedDataset(k, rounds, gap, delta);
    auto d = dataset.generate();
    //auto d = mod_2(k, rounds, gap);
    Exp3_average b(k, 0.1, 0.2);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(choice, d[choice][i]);
        }
    }
}


static void benchmark_exp3_defer_xi(benchmark::State& state) {
    auto k = 100;
    int xi = state.range(0);
    Exp3_deferred b(k, 0.1, xi);
    for (auto _ : state) {
        int rounds = 10000;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3(benchmark::State& state) {
    auto k = state.range(0);
    Exp3 b(k, 0.1);
    for (auto _ : state) {
        int rounds = 100;
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
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3_update(benchmark::State& state) {
    auto k = state.range(0);
    Exp3 b(k, 0.1);
    for (auto _ : state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_exp3_heap(benchmark::State& state) {
    auto k = state.range(0);
    Exp3_heap b(k, 0.1);
    for (auto _ : state) {

        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3_heap_sample(benchmark::State& state) {
    auto k = state.range(0);
    Exp3_heap b(k, 0.1);
    for (auto _ : state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3_heap_update(benchmark::State& state) {
    auto k = state.range(0);
    Exp3_heap b(k, 0.1);
    for (auto _ : state) {
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}
static void benchmark_exp3eta(benchmark::State& state) {
    auto k = state.range(0);
    Exp3Tor b(k, 0.1);
    for (auto _ : state) {
        int rounds = 100;
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
        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3eta_update(benchmark::State& state) {
    auto k = state.range(0);
    Exp3Tor b(k, 0.1);
    for (auto _ : state) {

        int rounds = 100;
        for (int i = 0; i < rounds; i++) {
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_tsallis_rv(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    auto g = StochasticallyConstrainedDataset(k, rounds, 1, 0.9);
    auto d = g.generate();
    Tsallis_RV b(k);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(choice, d[choice][i]);
        }
    }
}
static void benchmark_tsallis_iw(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    auto g = StochasticallyConstrainedDataset(k, rounds, 1, 0.9);
    auto d = g.generate();
    Tsallis_IW b(k);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(choice, d[choice][i]);
        }
    }
}

static void benchmark_tsallis_sample(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    auto g = StochasticallyConstrainedDataset(k, rounds, 1, 0.9);
    auto d = g.generate();
    Tsallis_IW b(k);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_tsallis_update(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    auto g = StochasticallyConstrainedDataset(k, rounds, 1, 0.9);
    auto d = g.generate();
    Tsallis_optimized b(k);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            //b.give_reward(choice, d[choice][i]);
        }
    }
}

static void benchmark_tsallis_optimized(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    auto g = StochasticallyConstrainedDataset(k, rounds, 1, 0.9);
    auto d = g.generate();
    Tsallis_optimized b(k);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            b.give_reward(choice, d[choice][i]);
        }
    }
}

static void benchmark_tsallis_optimized_sample(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    auto g = StochasticallyConstrainedDataset(k, rounds, 1, 0.9);
    auto d = g.generate();
    Tsallis_optimized b(k);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
        }
    }
}
static void benchmark_tsallis_optimized_update(benchmark::State& state) {
    auto k = state.range(0);
    int rounds = 100;
    auto g = StochasticallyConstrainedDataset(k, rounds, 1, 0.9);
    auto d = g.generate();
    Tsallis_optimized b(k);
    for (auto _ : state) {
        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            //b.give_reward(choice, d[choice][i]);
        }
    }
}


/*
BENCHMARK(benchmark_fpl)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_fpl_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_fpl_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);

BENCHMARK(benchmark_qbl)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_qbl_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_qbl_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
*/

/*
BENCHMARK(benchmark_fpl_hashing)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_fpl_hashing_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_fpl_hashing_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
*/
/*
BENCHMARK(benchmark_exp31)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_exp31_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_exp31_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);


//
//BENCHMARK(benchmark_exp3_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
//BENCHMARK(benchmark_exp3_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);

//BENCHMARK(benchmark_exp3)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(1);
//BENCHMARK(benchmark_exp3_defer)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(1);

//BENCHMARK(benchmark_exp3_data)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(1);
//BENCHMARK(benchmark_exp3_average)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(1);
/*



BENCHMARK(benchmark_exp3_heap_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_exp3_heap_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
*/

//BENCHMARK(benchmark_tsallis_rv)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(5);
BENCHMARK(benchmark_tsallis_iw)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(5);
BENCHMARK(benchmark_tsallis_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(5);
BENCHMARK(benchmark_tsallis_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(5);

BENCHMARK(benchmark_tsallis_optimized)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(5);
BENCHMARK(benchmark_tsallis_optimized_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(5);
BENCHMARK(benchmark_tsallis_optimized_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(5);

/*
BENCHMARK(benchmark_ucb_exp3)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_ucb_fpl)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);


BENCHMARK(benchmark_exp3m_1)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_exp3m_1_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);

BENCHMARK(benchmark_exp3m_1_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);


BENCHMARK(benchmark_exp3eta)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_exp3eta_sample)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
BENCHMARK(benchmark_exp3eta_update)->Arg(1)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
*/
BENCHMARK_MAIN();