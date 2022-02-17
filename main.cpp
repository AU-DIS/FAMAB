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
#include "algorithms/Exp3m.h"
#include "algorithms/Exp31.h"
#include <tuple>

/*
BENCHMARK(BM_FPL);
BENCHMARK(BM_Exp3);
BENCHMARK_MAIN();
*/

int main() {
    int K = 10;
    int k = 1;
    int round_factor = 1000;
    auto d = debug_simple_stochastic(K, k);

    int rounds = round_factor * K;

    double gamma = 0.7;
    VectorWeightStrategy vws(d.k, gamma);
    Exp3RewardStrategy exp3rs(&vws);
    Exp3Bandit b(vws, exp3rs);

    std::vector<double> regrets = std::vector<double>();
    regrets.reserve(rounds);

    for (int i = 0; i < rounds; i++) {
        int choice = b.choose();
        double regret;
        double feedback = d.feedback(choice, regret);
        regrets.push_back(regret);
        b.give_reward(choice, feedback);
    }

    write_regret(regrets, "/tmp/regret.csv", d.reward_max - d.reward_min);
    write_weights(vws.get_weights(), "/tmp/weights.csv");
}




/*
void run_exp3m() {

    int K = 1000;
    int k = 10;
    int round_factor = 100;
    auto d = debug_simple_stochastic(K, k);

    int rounds = round_factor * k;
    double log_factor = log(K/k)*K;

    double denom = (exp(1.0) - 1.0)*(double)rounds * (double)k;
    double gamma = sqrt(log_factor / denom);
    gamma = std::min(1.0, gamma);

    Exp3m b(K, k, gamma);

    std::vector<double> regrets = std::vector<double>();
    regrets.reserve(rounds);
    for (int i = 0; i < rounds; i++) {
        std::cout << "round: " << i << "\t";
        auto choices = b.choose();

        double acc_reward = 0;
        double acc_regret = 0;
        std::vector<double> rewards;
        for (auto choice : choices) {
            double regret = 0;
            double feedback = d.feedback(choice, regret);
            std::cout << regret << "\t";
            rewards.push_back(feedback);
            acc_reward += feedback;
            acc_regret += regret;
        }
        std::cout << std::endl;

        b.give_reward(choices, rewards);
        regrets.push_back(acc_regret);
    }

    for (int i = 0; i < rounds; i++) {
        regrets[i]
    }


    write_regret(regrets, "/tmp/regret.csv", d.reward_max - d.reward_min);
    //write_weights(b._weights, "../benchmark_results/weights.csv");
}
 */
/*
void run_dexp3() {
    int k = 100;
    int round_factor = 20;
    auto d = debug_simple_stochastic(k);
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
 */