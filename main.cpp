#include <iostream>
#include "datasets/Dataset_movielens.h"
#include <benchmark/benchmark.h>
#include "algorithms/BanditConfigurator.cpp"
#include "algorithms/Exp3Bandit.h"


   /*
   BENCHMARK(BM_FPL);
   BENCHMARK(BM_Exp3);
   BENCHMARK_MAIN();
*/

int main() {
    //Example of loading dataset
    Dataset_movielens d = Dataset_movielens("../datasets/data_directory/movielens.csv");
    Exp3Bandit *b = standard_exp3(d.k, 0.1);

    for (int i = 0; i < 1000; i++) {
        int choice = b->choose();
        double regret = d.feedback(choice);
        std::cout << 1 - regret << std::endl;
        b->give_reward(choice, regret);
    }
}

