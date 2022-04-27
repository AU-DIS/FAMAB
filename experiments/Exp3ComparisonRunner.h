//
// Created by Mathias Ravn Tversted on 31/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3COMPARISONRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3COMPARISONRUNNER_H

#include <thread>
#include "../algorithms/Exp3Bandit/Exp3_deferred.h"
#include "../algorithms/Exp3Bandit/Exp3_average.h"
#include "../datasets/dataset.h"

//template <typename Dataset>
void run_exp3_adversarial_experiment(Dataset &d, int k, int rounds, int averages, double gap,
                                     const std::string &out_path = "/tmp/out") {


    std::vector<double> exp3_compare_regrets(rounds);
    std::vector<double> exp3_regrets(rounds);
    std::vector<double> uniform_regrets(rounds);

    for (int i = 0; i < averages; i++) {
        std::vector<std::vector<double>> data_matrix = d.generate();
        //Exp3_average exp3_compare(k, 0.2, 0.8);
        //Exp3_deferred exp3_compare(k, 0.2, 128);
        Exp31 exp3_compare(k);
        Exp3 exp3(k, 0.2);
        Uniformbandit uni(k);

        std::vector<double> exp3_compare_run;
        std::thread t1(basic_tsallis_runner<Exp31>, std::ref(exp3_compare), std::ref(data_matrix), rounds, std::ref(exp3_compare_run));

        std::vector<double> exp3_run;
        std::thread t2(basic_tsallis_runner<Exp3>, std::ref(exp3), std::ref(data_matrix), rounds, std::ref(exp3_run));

        std::vector<double> uniform_run;
        std::thread t3(basic_tsallis_runner<Uniformbandit>, std::ref(uni), std::ref(data_matrix), rounds,
                       std::ref(uniform_run));

        t1.join();
        t2.join();
        t3.join();

        for (int round = 0; round < rounds; round++) {
            exp3_compare_regrets[round] += exp3_compare_run[round];
            exp3_regrets[round] += exp3_run[round];
            uniform_regrets[round] += uniform_run[round];
        }
    }
    for (auto &v: exp3_compare_regrets) v /= averages;
    for (auto &v: exp3_regrets) v /= averages;
    for (auto &v: uniform_regrets) v /= averages;
    std::vector<std::vector<double>> result_matrix;
    result_matrix.push_back(exp3_compare_regrets);
    result_matrix.push_back(exp3_regrets);
    result_matrix.push_back(uniform_regrets);
    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
            description +
            std::to_string(k) + ","
            + std::to_string(rounds) + ","
            + std::to_string(gap) + ","
            + "Exp3 (average),Exp3,Uniform,";
    auto descriptions = std::vector<string>{
            "Exp3 (average)",
            "Exp3",
            "Uniform"
    };
    write_results(result_matrix, metadata, descriptions, out_path);
}




#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3COMPARISONRUNNER_H
