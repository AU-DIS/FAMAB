#include <iostream>
#include "datasets/Dataset_movielens.h"
#include <benchmark/benchmark.h>
#include "algorithms/Exp3Bandit/Exp3Bandit.h"
#include "algorithms/Exp3Bandit/VectorWeightStrategy.h"
#include "algorithms/Exp3Bandit/Exp3RewardStrategy.h"
#include "utilities/weight_exporter.cpp"
#include "datasets/debug_simple_stochastic.h"
# include "datasets/debug_simple_adversarial.h"
#include "algorithms/DExp3.h"
#include <tuple>

/*
BENCHMARK(BM_FPL);
BENCHMARK(BM_Exp3);
BENCHMARK_MAIN();
*/

int main() {
    size_t k = 100;
    int round_factor = 20;
    debug_simple_stochastic d = debug_simple_stochastic(k);
    double gamma = 0.1;
    int rounds = round_factor * d.k;
    DExp3 b(k, gamma, 0.8);

    std::vector<double> regrets = std::vector<double>();
    regrets.reserve(rounds);

    for (int i = 0; i < rounds; i++) {
        auto choices = b.choose();
        int choice1 = std::get<0>(choices);
        int choice2 = std::get<1>(choices);

        double feedback1 = d.feedback(choice1);
        double feedback2 = d.feedback(choice2);

        regrets.push_back(2 - (feedback1 + feedback2));
        int winner = feedback1 > feedback2 ? 1 : 0;
        b.give_reward(choice1, choice2, winner, i);
    }
    write_regret(regrets, "../benchmark_results/regret.csv");
    write_weights(b._weights, "../benchmark_results/weights.csv");

}


void run_exp3() {
    //Example of loading dataset
    //Dataset_movielens d = Dataset_movielens("../datasets/data_directory/movielens.csv");
    int k = 100;
    int round_factor = 100000;
    debug_simple_adversarial d = debug_simple_adversarial(k, k * round_factor);


    // These {} are for scoping and garbage collection
    {
        double gamma = 0.1;
        VectorWeightStrategy vws(d.k, gamma);
        Exp3RewardStrategy exp3rs(&vws);
        Exp3Bandit b(vws, exp3rs);


        int rounds = round_factor * d.k;
        std::vector<double> regrets = std::vector<double>();
        regrets.reserve(rounds);

        for (int i = 0; i < rounds; i++) {
            int choice = b.choose();
            double feedback = d.feedback(choice);
            regrets.push_back(1 - feedback);
            b.give_reward(choice, feedback);
        }

        write_regret(regrets, "../benchmark_results/regret.csv");
        write_weights(vws.get_weights(), "../benchmark_results/weights.csv");
    }
}