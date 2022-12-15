
// Created by Mathias Ravn Tversted on 1/03/2022.
#include "iostream"
#include <benchmark/benchmark.h>
#include "random"
#include "algorithms/FPL/FPL.h"
#include "algorithms/FPL/QBL.h"
#include "algorithms/FPL/FPL_hash.h"
#include "algorithms/Exp3Bandit/Exp31.h"
#include "algorithms/Exp3Bandit/Exp3.1_optimized.h"
#include "algorithms/Exp3Bandit/Exp3.h"
//#include "algorithms/Tsallis-INF/TsallisINF.h"
//#include "algorithms/Tsallis-INF/Tsallis_RV.h"
//#include "algorithms/Tsallis-INF/Tsallis_IW.h"
//#include "algorithms/Tsallis-INF/Tsallis_LTU.h"
//#include "algorithms/Tsallis-INF/Tsallis_approx_rv.h"
//#include "algorithms/Tsallis-INF/Tsallis_Heap.h"
//#include "algorithms/DEXP/DExp3.h"
#include "algorithms/Exp3m/DepRoundALIASStrategy.h"
#include "algorithms/Exp3m/Exp3m.h"
#include "algorithms/Exp3m/Exp3m_heap.h"
#include "algorithms/Exp3m/Exp31m.h"
#include "algorithms/FPL/FPL_buckets.h"
#include "algorithms/FPL/FPL_toplog.h"
#include "algorithms/UCB/UCB1.h"
#include "algorithms/Exp3Bandit/Exp3Tor.h"
#include "algorithms/Exp3Bandit/Exp3_heap.h"
#include "algorithms/Exp3Bandit/Exp3_fid.h"
#include "algorithms/Exp3Bandit/Exp3_lad.h"
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
//#include "benchmarks/Tsallis_iw.h"
//#include "benchmarks/Tsallis_LTU.h"
//#include "benchmarks/Tsallis_approx_rv.h"
//#include "benchmarks/Tsallis_rv.h"
#include "benchmarks/UCB.h"

// ->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_qbl)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1)->Unit(benchmark::kMillisecond);
//BENCHMARK(benchmark_qbl_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
//BENCHMARK(benchmark_qbl_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1)->Unit(benchmark::kMillisecond);

//BENCHMARK(benchmark_fpl)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1)->Unit(benchmark::kMillisecond);
//BENCHMARK(benchmark_fpl_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
//BENCHMARK(benchmark_fpl_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);

//BENCHMARK(benchmark_fpl_toplog)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1)->Unit(benchmark::kMillisecond);
//BENCHMARK(benchmark_fpl_toplog_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
//BENCHMARK(benchmark_fpl_toplog_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

//BENCHMARK(benchmark_fpl_hashing)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
//BENCHMARK(benchmark_fpl_hashing_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
//BENCHMARK(benchmark_fpl_hashing_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);

//BENCHMARK(benchmark_exp3)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1)->Unit(benchmark::kMillisecond);
//BENCHMARK(benchmark_exp3_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
//BENCHMARK(benchmark_exp3_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
/*
BENCHMARK(benchmark_exp3_fid)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp3_fid_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp3_fid_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_exp3_lad)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp3_lad_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp3_lad_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
*/
BENCHMARK(benchmark_exp3_heap)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1)->Unit(benchmark::kMillisecond);
//BENCHMARK(benchmark_exp3_heap_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
//BENCHMARK(benchmark_exp3_heap_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(1);
/*
BENCHMARK(benchmark_exp31)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp31_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp31_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_exp31_optimized)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp31_optimized_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp31_optimized_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);


BENCHMARK(benchmark_exp31)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp31_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_exp31_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_tsallis_iw)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_iw_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_iw_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_tsallis_rv)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_rv_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_rv_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_tsallis_ltu)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_ltu_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_ltu_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_tsallis_approxrv)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_approxrv_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_approxrv_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);

BENCHMARK(benchmark_tsallis_heap)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_heap_sample)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
BENCHMARK(benchmark_tsallis_heap_update)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Threads(8);
*/

BENCHMARK_MAIN();