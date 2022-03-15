//
// Created by Mathias Ravn Tversted on 03/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXPLORENOMORERUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXPLORENOMORERUNNER_H
#include "../datasets/dataset_explore_no_more.h"
#include "../algorithms/Exp3Bandit/Exp3TorRewardStrategy.h"
#include "../algorithms/Exp3Bandit/Exp3IXTorRewardStrategy.h"
#include "../algorithms/Exp3Bandit/Exp3VectorWeightStrategy.h"
#include "../algorithms/Exp3Bandit/Exp31.h"
#include "../algorithms/Exp3Bandit/Exp3Bandit.h"
#include "../algorithms/FPL/FPLVectorWeightStrategy.h"
#include "../algorithms/FPL/NaiveRandomGenStrategy.h"
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/Tsallis-INF/TsallisINF.h"
#include "../utilities/standard_deviation.cpp"
#include "../utilities/eta_mean_std_writer.h"
#include "../runner.h"
#include <stdlib.h>

void run_explore_no_more_experiment() {
    int K = 10;
    int rounds = 1000000;

    std::vector<std::vector<double>> data_matrix;
    for (int eta_index = 0; eta_index < 10; eta_index++) {
        auto eta = pow(10, ((double)eta_index)/2.5-2);
        std::cout << "eta" << std::endl;
        std::cout << std::to_string(eta_index) << std::endl;
        std::cout << std::to_string(eta) << std::endl;
        std::vector<double> exp3_regret_T_half;
        std::vector<double> exp3_regret_T;
        std::vector<double> exp3IX_regret_T_half;
        std::vector<double> exp3IX_regret_T;
        exp3_regret_T_half.reserve(20);
        exp3_regret_T.reserve(20);
        exp3IX_regret_T_half.reserve(20);
        exp3IX_regret_T.reserve(20);
        for (int i = 0; i < 20; i++) {
            auto d = dataset_explore_no_more(rounds);
            Exp3VectorWeightStrategy ws(K, eta/2);
            Exp3TorRewardStrategy rs(ws, eta);
            Exp3VectorWeightStrategy wsIX(K, eta/2);
            Exp3IXTorRewardStrategy rsIX(wsIX, eta);
            Exp3Bandit exp3(ws, rs);
            Exp3Bandit exp3IX(wsIX, rsIX);
            std::cout << "1" << std::endl;
            auto exp3_regrets = basic_runner(exp3, d, rounds);
            std::cout << "2" << std::endl;
            auto exp3IX_regrets = basic_runner(exp3IX, d, rounds);
            std::cout << "3" << std::endl;
            exp3_regret_T_half.push_back(exp3_regrets[rounds/2]);
            exp3_regret_T.push_back(exp3_regrets[rounds]);
            exp3IX_regret_T_half.push_back(exp3IX_regrets[rounds/2]);
            exp3IX_regret_T.push_back(exp3IX_regrets[rounds]);
            exp3_regrets.clear();
            exp3IX_regrets.clear();
        }
        auto [mean_exp3_T_half, std_exp3_T_half] = standard_deviation(exp3_regret_T_half);
        auto [mean_exp3_T, std_exp3_T] = standard_deviation(exp3_regret_T);
        auto [mean_exp3IX_T_half, std_exp3IX_T_half] = standard_deviation(exp3IX_regret_T_half);
        auto [mean_exp3IX_T, std_exp3IX_T] = standard_deviation(exp3IX_regret_T);
        data_matrix.push_back({eta, mean_exp3_T_half, std_exp3_T_half, mean_exp3_T, std_exp3_T, mean_exp3IX_T_half, std_exp3IX_T_half, mean_exp3IX_T, std_exp3IX_T});
        std::cout << "end" << std::endl;
    }

    auto comments =
            "#Explore No More,"
            + std::to_string(K) + ","
            + std::to_string(rounds);
    auto header = "eta,mean_regret_exp3_T_half,std_regret_exp3_T_half,mean_regret_exp3_T,std_regret_exp3_T,mean_regret_exp3IX_T_half,std_regret_exp3IX_T_half,mean_regret_exp3IX_T,std_regret_exp3IX_T";
    write_results(data_matrix, comments, header, "/tmp/explore_no_more.csv");
}

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXPLORENOMORERUNNER_H
