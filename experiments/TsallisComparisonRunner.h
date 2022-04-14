//
// Created by Mathias Tversted on 12/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_TSALLISCOMPARISONRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_TSALLISCOMPARISONRUNNER_H

#include "../algorithms/Tsallis-INF/IW.h"
#include "../algorithms/Tsallis-INF/RV.h"
#include "../algorithms/Tsallis-INF/TsallisINF.h"
#include "../algorithms/Tsallis-INF/Tsallis_optimized.h"
#include "../algorithms/Tsallis-INF/Tsallis_IW.h"
#include "../algorithms/Tsallis-INF/Tsallis_RV.h"


template <typename Dataset>
void run_tsallis_adversarial_experiment(Dataset d, int k, int rounds, int averages, double gap,
                                    const std::string &out_path = "/tmp/out") {


    std::vector<double> tsallis_iw_regrets(rounds);
    std::vector<double> tsallis_rv_regrets(rounds);
    std::vector<double> tsallis_optimized_regrets(rounds);
    std::vector<double> uniform_regrets(rounds);

    for (int i = 0; i < averages; i++) {
        std::vector<std::vector<double>> data_matrix = d.generate();

        Tsallis_IW iw(k);
        Tsallis_RV rv(k);
        Tsallis_optimized optimized(k);
        Uniformbandit uni(k);

        std::vector<double> tsallis_iw_run;
        std::thread t1(basic_tsallis_runner<Tsallis_IW>, std::ref(iw), std::ref(data_matrix), rounds, std::ref(tsallis_iw_run));

        std::vector<double> tsallis_rv_run;
        std::thread t2(basic_tsallis_runner <Tsallis_RV>, std::ref(rv), std::ref(data_matrix), rounds, std::ref(tsallis_rv_run));

        std::vector<double> tsallis_optimized_run;
        std::thread t4(basic_tsallis_runner <Tsallis_optimized>, std::ref(optimized), std::ref(data_matrix), rounds, std::ref(tsallis_optimized_run));

        std::vector<double> uniform_run;
        std::thread t3(basic_tsallis_runner<Uniformbandit>, std::ref(uni), std::ref(data_matrix), rounds,
                       std::ref(uniform_run));

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        for (int round = 0; round < rounds; round++) {
            tsallis_iw_regrets[round] += tsallis_iw_run[round];
            tsallis_rv_regrets[round] += tsallis_rv_run[round];
            tsallis_optimized_regrets[round] += tsallis_optimized_run[round];
            uniform_regrets[round] += uniform_run[round];
        }
    }
    for (auto &v: tsallis_iw_regrets) v /= averages;
    for (auto &v: tsallis_rv_regrets) v /= averages;
    for (auto &v: tsallis_optimized_regrets) v /= averages;
    for (auto &v: uniform_regrets) v /= averages;
    std::vector<std::vector<double>> result_matrix;
    result_matrix.push_back(tsallis_iw_regrets);
    result_matrix.push_back(tsallis_rv_regrets);
    result_matrix.push_back(tsallis_optimized_regrets);
    result_matrix.push_back(uniform_regrets);
    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
            description +
            std::to_string(k) + ","
            + std::to_string(rounds) + ","
            + std::to_string(gap) + ","
            + "Tsallis (IW),Tsallis (RV),Tsallis (IW with optimisations),Uniform,";
    auto descriptions = std::vector<string>{
            "Tsallis (IW)",
            "Tsallis (RV)",
            "Tsallis (IW with optimisations)",
            "Uniform"
    };
    write_results(result_matrix, metadata, descriptions, out_path);
}



#endif //EFFICIENT_MULTI_ARMED_BANDITS_TSALLISCOMPARISONRUNNER_H
