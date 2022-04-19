//
// Created by Mathias Ravn Tversted on 05/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPLCOMPARISONRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPLCOMPARISONRUNNER_H

#include <thread>
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/FPL/FPL_hash.h"
#include "../algorithms/FPL/FPL_buckets.h"
#include "../algorithms/FPL/FPL_weightless.h"

template <typename Dataset>
void run_fpl_tsallis_experiment(Dataset d, int k, int rounds, int averages, double gap,
                                 const std::string &out_path = "/tmp/out") {


    std::vector<double> fpl_original_regrets(rounds);
    std::vector<double> fpl_new_regrets(rounds);
    std::vector<double> uniform_regrets(rounds);

    for (int i = 0; i < averages; i++) {
    std::vector<std::vector<double>> data_matrix = d.generate();
        FPLVectorWeightStrategy fpl_ws(k);
        NaiveRandomGenStrategy fpl_rs(k, 0.9);
        FPL fpl(fpl_ws, fpl_rs);

        FPL_hash fpl_new(k, 0.9, rounds);
        //FPL_buckets fpl_new(k, 0.9);
//        FPL_weightless fpl_new(k, 0.9);

        Uniformbandit uni(k);

        std::vector<double> fpl_original_run;
        std::thread t1(basic_tsallis_runner<FPL<FPLVectorWeightStrategy, NaiveRandomGenStrategy>>, std::ref(fpl), std::ref(data_matrix), rounds, std::ref(fpl_original_run));

        std::vector<double> fpl_new_run;
        std::thread t2(basic_tsallis_runner<FPL_hash>, std::ref(fpl_new), std::ref(data_matrix), rounds, std::ref(fpl_new_run));

        std::vector<double> uniform_run;
        std::thread t3(basic_tsallis_runner<Uniformbandit>, std::ref(uni), std::ref(data_matrix), rounds,
                       std::ref(uniform_run));

        t1.join();
        t2.join();
        t3.join();

        for (int round = 0; round < rounds; round++) {
            fpl_original_regrets[round] += fpl_original_run[round];
            fpl_new_regrets[round] += fpl_new_run[round];
            uniform_regrets[round] += uniform_run[round];
        }
    }
    for (auto &v: fpl_original_regrets) v /= averages;
    for (auto &v: fpl_new_regrets) v /= averages;
    for (auto &v: uniform_regrets) v /= averages;
    std::vector<std::vector<double>> result_matrix;
    result_matrix.push_back(fpl_original_regrets);
    result_matrix.push_back(fpl_new_regrets);
    result_matrix.push_back(uniform_regrets);
    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
            description +
            std::to_string(k) + ","
            + std::to_string(rounds) + ","
            + std::to_string(gap) + ","
            + "FPL,FPL (Hashing),Uniform,";
    auto descriptions = std::vector<string>{
            "FPL",
            "FPL (Hashing)",
            "Uniform"
    };
    write_results(result_matrix, metadata, descriptions, out_path);
}



#endif //EFFICIENT_MULTI_ARMED_BANDITS_FPLCOMPARISONRUNNER_H
