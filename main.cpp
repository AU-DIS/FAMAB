#include <iostream>
#include "algorithms/Exp3.h"
#include "experiments/fpl/fpl_mod2.cpp"
#include "experiments/exp3/exp3_mod2.cpp"
#include <benchmark/benchmark.h>



   /*
   BENCHMARK(BM_FPL);
   BENCHMARK(BM_Exp3);
   BENCHMARK_MAIN();
*/

int main() {
    run_fpl_mod2_bandit(1, 1000, 50);

}

