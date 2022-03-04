//
// Created by Mathias Ravn Tversted on 03/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_GENERICBANDITRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_GENERICBANDITRUNNER_H
#include "../datasets/dataset_simple_adversarial.h"
#include "../algorithms/Exp3Bandit/Exp3RewardStrategy.h"
#include "../algorithms/Exp3Bandit/Exp3VectorWeightStrategy.h"
#include "../utilities/weight_exporter.cpp"
#include "../algorithms/Exp3Bandit/Exp31.h"
#include "../algorithms/Exp3Bandit/Exp3Bandit.h"
#include "../algorithms/FPL/FPLVectorWeightStrategy.h"
#include "../algorithms/FPL/NaiveRandomGenStrategy.h"
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/Tsallis-INF/TsallisINF.h"
#include "../runner.h"
#include "../utilities/result_writer.h"

void run_generic_experiment() {
    int K = 10;
    int round_factor = 1000;
    int rounds = K * round_factor;
    auto d = dataset_simple_adversarial(K, rounds);

    Exp3VectorWeightStrategy ws31(K, 0.1);
    Exp3RewardStrategy rs31(ws31);
    Exp3VectorWeightStrategy ws(K, 0.1);
    Exp3RewardStrategy rs(ws);
    FPLVectorWeightStrategy fpl_ws(K);
    NaiveRandomGenStrategy fpl_rs(K, 0.2);

    Exp3Bandit exp3(ws, rs);
    Exp31 exp31(ws31, rs31);
    TsallisINF tsallis(K);
    FPL fpl(fpl_ws, fpl_rs);


    std::vector<std::vector<double>> data_matrix;
    data_matrix.push_back(basic_runner(exp3, d, rounds));
    data_matrix.push_back(basic_runner(exp31, d, rounds));
    data_matrix.push_back(basic_runner(tsallis, d, rounds));
    data_matrix.push_back(basic_runner(fpl, d, rounds));


    // MUST CONTAIN ENDING COMMA
    auto description = "Adversarial dataset,";
    auto metadata =
            description +
            std::to_string(K) + ","
            + std::to_string(rounds) + ","
            + std::to_string(d.expected_value()) + ","
            + "Exp3,Exp3.1,Tsallis-INF,FPL";
    auto descriptions = std::vector<string>{
            "Exp3",
            "Exp3.1",
            "Tsallis-INF",
            "FPL"
    };
    write_results(data_matrix, metadata, descriptions, "/tmp/regret");
}

#endif //EFFICIENT_MULTI_ARMED_BANDITS_GENERICBANDITRUNNER_H
