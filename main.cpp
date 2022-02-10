#include <iostream>
#include "datasets/Dataset_movielens.h"
#include <benchmark/benchmark.h>
#include "algorithms/Exp3Bandit.h"
#include "algorithms/VectorWeightStrategy.h"
#include "algorithms/Exp3RewardStrategy.h"
#include "utilities/weight_exporter.cpp"

/*
BENCHMARK(BM_FPL);
BENCHMARK(BM_Exp3);
BENCHMARK_MAIN();
*/

int main() {
    //Example of loading dataset
    Dataset_movielens d = Dataset_movielens("../datasets/data_directory/movielens.csv");

    // These {} are for scoping and garbage collection
    {
        double gamma = 0.5;
        VectorWeightStrategy vws(d.k, gamma);
        Exp3RewardStrategy exp3rs(&vws);
        Exp3Bandit b(vws, exp3rs);


        int rounds = 10000;
        std::vector<double> regrets = std::vector<double>();
        regrets.reserve(rounds);

        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            double feedback = d.feedback(choice);
            regrets.push_back(1 - feedback);
            b.give_reward(choice, feedback);
        }

        write_regret(regrets, "../benchmark_results/regret.csv");
       write_weights(b._weightStrategy.get_weights(), "../benchmark_results/weights.csv");
    }
}

