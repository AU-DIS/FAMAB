#include <iostream>
#include "datasets/Dataset_movielens.h"
#include <benchmark/benchmark.h>
#include "algorithms/Exp3Bandit.h"
#include "algorithms/VectorWeightStrategy.h"
#include "algorithms/Exp3RewardStrategy.h"


/*
BENCHMARK(BM_FPL);
BENCHMARK(BM_Exp3);
BENCHMARK_MAIN();
*/

int main() {
    //Example of loading dataset
    Dataset_movielens d = Dataset_movielens("../datasets/data_directory/movielens.csv");

    {
        double gamma = 0.3;
        VectorWeightStrategy vws(d.k, gamma);
        Exp3RewardStrategy exp3rs(&vws);
        Exp3Bandit b(vws, exp3rs);


        int rounds = 1000;
        std::vector<double> regrets = std::vector<double>();
        regrets.reserve(rounds);

        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            double regret = d.feedback(choice);
            regrets[i] = regret;
            std::cout << 1 - regret << std::endl;
            b.give_reward(choice, regret);
        }
    }
}

