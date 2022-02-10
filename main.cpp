#include <iostream>
#include "datasets/Dataset_movielens.h"
#include <benchmark/benchmark.h>


   /*
   BENCHMARK(BM_FPL);
   BENCHMARK(BM_Exp3);
   BENCHMARK_MAIN();
*/

int main() {
    //Example of loading dataset
    Dataset_movielens d = Dataset_movielens("../datasets/data_directory/movielens.csv");
}

