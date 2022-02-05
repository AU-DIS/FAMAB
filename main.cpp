#include <iostream>
#include "algorithms/Exp3.h"
#include "experiments/fpl/fpl_mod2.cpp"
#include "experiments/exp3/exp3_mod2.cpp"
#include <benchmark/benchmark.h>



   BENCHMARK(BM_FPL)->Iterations(5);
   BENCHMARK(BM_Exp3)->Iterations(5);
    BENCHMARK_MAIN();

