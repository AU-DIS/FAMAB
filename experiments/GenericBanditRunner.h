//
// Created by Mathias Ravn Tversted on 03/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_GENERICBANDITRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_GENERICBANDITRUNNER_H
#include "../datasets/dataset_simple_adversarial.h"
#include "../datasets/dataset_simple_stochastic.h"
#include "../datasets/Dataset_movielens.h"
#include "../algorithms/Exp3Bandit/Exp3RewardStrategy.h"
#include "../algorithms/Exp3Bandit/Exp3VectorWeightStrategy.h"
#include "../utilities/weight_exporter.cpp"
#include "../algorithms/Exp3Bandit/Exp31.h"
#include "../algorithms/Exp3Bandit/Exp3Bandit.h"
#include "../algorithms/FPL/FPLVectorWeightStrategy.h"
#include "../algorithms/FPL/NaiveRandomGenStrategy.h"
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/Tsallis-INF/TsallisINF.h"
#include "../algorithms/Tsallis-INF/TsallisIW.h"
#include "../algorithms/Tsallis-INF/TsallisRV.h"
#include "../runner.h"
#include "../algorithms/Uniformbandit.h"
#include "../utilities/result_writer.h"

template <typename Dataset>
void run_generic_experiment(Dataset d, int K = 10, int rounds = 100, int averages=1, const std::string& out_path="/tmp/out") {
    //auto d = Dataset_movielens("../datasets/data_directory/movielens.csv", 4);
    Exp3VectorWeightStrategy ws31(K, 0.1);
    Exp3RewardStrategy rs31(ws31);
    Exp3VectorWeightStrategy ws(K, 0.1);
    Exp3RewardStrategy rs(ws);
    FPLVectorWeightStrategy fpl_ws(K);
    NaiveRandomGenStrategy fpl_rs(K, 0.2);

    Exp3Bandit exp3(ws, rs);
    Exp31 exp31(ws31, rs31);
    TsallisIW iw;
    TsallisINF tsallis_iw(K, iw);
    TsallisRV rv;
    TsallisINF tsallis_rv(K, rv);
    FPL fpl(fpl_ws, fpl_rs);
    Uniformbandit uni(K);

    std::vector<double> exp3_regrets(rounds);
    std::vector<double> exp31_regrets(rounds);
    std::vector<double> tsallis_iw_regrets(rounds);
    std::vector<double> tsallis_rv_regrets(rounds);
    std::vector<double> fpl_regrets(rounds);
    std::vector<double> uni_regrets(rounds);
    for (int i = 0; i < averages; i++) {
        auto exp3_run = basic_runner(exp3, d, rounds);
        auto exp31_run = basic_runner(exp31, d, rounds);
        auto tsallis_iw_run = basic_runner(tsallis_iw, d, rounds);
        auto tsallis_rv_run = basic_runner(tsallis_rv, d, rounds);
        auto fpl_run = basic_runner(fpl, d, rounds);
        auto uni_run = basic_runner(uni, d, rounds);
        for (int round = 0; round < rounds; round++) {
            exp3_regrets[round] += exp3_run[round];
            exp31_regrets[round] += exp31_run[round];
            tsallis_iw_regrets[round] += tsallis_iw_run[round];
            tsallis_rv_regrets[round] += tsallis_rv_run[round];
            fpl_regrets[round] += fpl_run[round];
            uni_regrets[round] += uni_run[round];
        }
    }
    for (auto &v : exp3_regrets) v /= averages;
    for (auto &v : exp31_regrets) v /= averages;
    for (auto &v : tsallis_iw_regrets) v /= averages;
    for (auto &v : tsallis_rv_regrets) v /= averages;
    for (auto &v : fpl_regrets) v /= averages;
    for (auto &v : uni_regrets) v /= averages;

    std::vector<std::vector<double>> data_matrix;
    data_matrix.push_back(exp3_regrets);
    data_matrix.push_back(exp31_regrets);
    data_matrix.push_back(tsallis_iw_regrets);
    data_matrix.push_back(tsallis_rv_regrets);
    data_matrix.push_back(fpl_regrets);
    data_matrix.push_back(uni_regrets);

    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
            description +
            std::to_string(K) + ","
            + std::to_string(rounds) + ","
            + std::to_string(d.expected_value()) + ","
            + "Exp3,Exp3.1,Tsallis-INF (IW),Tsallis-INF(RV),FPL,Uniform";
    auto descriptions = std::vector<string>{
            "Exp3",
            "Exp3.1",
            "Tsallis-INF (IW)",
            "Tsallis-INF (RV)",
            "FPL",
            "Uniform"
    };
    write_results(data_matrix, metadata, descriptions, out_path);
}

#endif //EFFICIENT_MULTI_ARMED_BANDITS_GENERICBANDITRUNNER_H
