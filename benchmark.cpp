
// Created by Mathias Ravn Tversted on 1/03/2022.
#include "iostream"
#include <benchmark/benchmark.h>
#include "random"
#include "algorithms/FPL/FPL.h"
#include "algorithms/FPL/FPL_hash.h"
#include "algorithms/Exp3Bandit/Exp31.h"
#include "algorithms/Exp3Bandit/Exp3.h"
#include "algorithms/Tsallis-INF/TsallisINF.h"
#include "algorithms/Tsallis-INF/RV.h"
#include "algorithms/Tsallis-INF/IW.h"
#include "algorithms/Tsallis-INF/Tsallis_RV.h"
#include "algorithms/Tsallis-INF/Tsallis_IW.h"
#include "algorithms/Tsallis-INF/Tsallis_LTU.h"
#include "algorithms/DEXP/DExp3.h"
#include "algorithms/Exp3m/DepRoundALIASStrategy.h"
#include "algorithms/Exp3m/Exp3m.h"
#include "algorithms/Exp3m/Exp31m.h"
#include "algorithms/FPL/FPL_buckets.h"
#include "algorithms/FPL/FPL_toplog.h"
#include "algorithms/UCB/UCB1.h"
#include "algorithms/Exp3Bandit/Exp3Tor.h"
#include "algorithms/Exp3Bandit/Exp3_heap.h"
#include "algorithms/Exp3Bandit/Exp3_deferred.h"
#include "algorithms/Exp3Bandit/Exp3_average.h"
#include "experiments/AdversarialExperimentRunner.h"
#include "datasets/data_generators.h"

#include "benchmarks/Exp3_dum.h"
#include "benchmarks/Exp3_eta.h"
#include "benchmarks/Exp3_heap.h"
#include "benchmarks/Exp3.1.h"
#include "benchmarks/Exp3.h"
#include "benchmarks/Exp3m.h"
#include "benchmarks/FPL_H.h"
#include "benchmarks/FPL.h"
#include "benchmarks/FPL_buckets.h"
#include "benchmarks/FPL_toplog.h"
#include "benchmarks/QBL.h"
#include "benchmarks/Tsallis_iw.h"
#include "benchmarks/Tsallis_LTU.h"
#include "benchmarks/Tsallis_rv.h"
#include "benchmarks/UCB.h"


/*
BENCHMARK(benchmark_fpl)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(8);
BENCHMARK(benchmark_fpl_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(8);
BENCHMARK(benchmark_fpl_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(8);
*/

BENCHMARK(benchmark_fpl_toplog)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(8);
BENCHMARK(benchmark_fpl_toplog_sample)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(8);
BENCHMARK(benchmark_fpl_toplog_update)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Threads(8);


BENCHMARK_MAIN();