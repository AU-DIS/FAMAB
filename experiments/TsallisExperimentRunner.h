//
// Created by Mathias Ravn Tversted on 15/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_TSALLISEXPERIMENTRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_TSALLISEXPERIMENTRUNNER_H


#include "../algorithms/Exp3m/DepRoundALIASStrategy.h"
#include "../algorithms/Exp3m/Exp3m.h"
#include "../algorithms/Uniformbandit.h"
#include "../utilities/result_writer.h"
#include "../runner.h"
#include "../algorithms/FPL/FPLVectorWeightStrategy.h"
#include "../algorithms/FPL/NaiveRandomGenStrategy.h"
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/FPL/FPL_weightless.h"
#include "../algorithms/Exp3Bandit/Exp3.h"
#include "../algorithms/Exp3Bandit/Exp31.h"
#include "../algorithms/Tsallis-INF/TsallisINF.h"
#include "../algorithms/Tsallis-INF/TsallisRV.h"
#include "../algorithms/Tsallis-INF/TsallisIW.h"
#include "../algorithms/UCB/UCB1.h"


template<typename Dataset>
void run_tsallis_weight_experiment(Dataset d, int k, int rounds, double gap,
                                   int averages = 50, const std::string &regret_out_path = "/tmp/out",
                                   const std::string &weight_out_path = "/tmp/out",
                                   const std::string &algorithm = "Exp3") {
    std::vector<std::vector<double>> regrets;
    std::vector<double> bandit_regrets(rounds, 0);
    std::vector<double> uniform_regrets(rounds, 0);

    std::vector<std::vector<double>> weights_at_r;
    int interval_changes = std::floor(std::log2(rounds) / std::log2(3.2));
    for (int i = 0; i < interval_changes; i++) {
        std::vector<double> weights(k, 0);
        weights_at_r.push_back(weights);
    }

    for (int avg = 0; avg < averages; avg++) {
        std::vector<std::vector<double>> data_matrix = d.generate();
        FPLVectorWeightStrategy fpl_ws(k);
        NaiveRandomGenStrategy fpl_rs(k, 10);
        FPL fpl(fpl_ws, fpl_rs);
        Uniformbandit uni(k);

//        Exp3 fpl(k, 0.1);

        int multiple = 1;
        int interval = 0;
        for (int round = 0; round < rounds; round++) {
            double threshold = pow(gap, multiple);
            if (round > threshold) {
                auto w = fpl.get_weights();
                for (int j = 0; j < k; j++) {
                    weights_at_r[interval][j] += (w[j] / averages);
                }
                interval++;
                multiple++;
            }
            auto bandit_choice = fpl.choose();
            auto bandit_reward = data_matrix[bandit_choice][round];
            auto uniform_choice = uni.choose();
            auto uni_reward = data_matrix[uniform_choice][round];
            double max_element = 0;
            for (auto &arm: data_matrix) {
                if (arm[round] >= max_element) max_element = arm[round];
            }
            double bandit_regret = max_element - bandit_reward;
            double uniform_regret = max_element - uni_reward;
            fpl.give_reward(bandit_choice, bandit_reward);
            bandit_regrets[round] += (bandit_regret / averages);
            uniform_regrets[round] += (uniform_regret / averages);
        }
    }


    regrets.push_back(bandit_regrets);
    regrets.push_back(uniform_regrets);

    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
            description +
            std::to_string(k) + ","
            + std::to_string(rounds) + ","
            + std::to_string(gap) + ","
            + algorithm + ",uniform,";
    auto descriptions = std::vector<std::string>{
            algorithm,
            "Uniform"
    };

    auto weights_metadata = "";
    auto weights_descriptions = std::vector<std::string>{
            ""
    };

    write_results(regrets, metadata, descriptions, regret_out_path);
    write_results(weights_at_r, weights_metadata, weights_descriptions, weight_out_path);
}
template<typename Dataset>
void run_tsallis_exp3m_experiment(Dataset d, int k, int K, int rounds, int averages,
                                  double gap,
                                  const std::string &out_path = "/tmp/out") {

    std::vector<double> uniform_regrets(rounds);
    std::vector<double> exp3m_regrets(rounds);
    for (int avg = 0; avg < averages; avg++) {
        std::vector<std::vector<double>> data_matrix = d.generate();
        Uniformbandit uni(k);
        DepRoundALIASStrategy a;
        Exp3m b(k, K, 0.1, a);
        for (int round = 0; round < rounds; round++) {
            std::vector<double> uniform_rewards(K, 0);
            std::vector<double> exp3m_rewards(K, 0);
            std::vector<double> round_uniform_regrets(K, 0);
            std::vector<double> round_exp3m_regrets(K, 0);


            auto choices = b.choose();
            double uniform_regret = 0;
            double uniform_reward = 0;
            double exp3m_regret = 0;
            double exp3m_reward = 0;
            auto max_choice = 0;
            for (int i = 0; i < k; i++) {
                if (data_matrix[i][round] > max_choice) max_choice = data_matrix[i][round];
            }

            for (int c = 0; c < K; c++) {
                auto uni_choice = uni.choose();
                auto exp3m_choice = choices[c];

                uniform_reward += data_matrix[uni_choice][round];
                exp3m_reward += data_matrix[exp3m_choice][round];
            }
            uniform_regret = ((max_choice*K) - uniform_reward)/K;
            exp3m_regret = ((max_choice*K) - exp3m_reward)/K;
            uniform_regrets[round] += uniform_regret/averages;
            exp3m_regrets[round] += exp3m_regret/averages;
        }
    }
    std::vector<std::vector<double>> result_matrix;
    result_matrix.push_back(uniform_regrets);
    result_matrix.push_back(exp3m_regrets);

    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
            description +
            std::to_string(k) + ","
            + std::to_string(rounds) + ","
            + std::to_string(gap) + ","
            + std::to_string(K) + ","
            + "Uniform,Exp3m";
    auto descriptions = std::vector<string>{
        "Uniform",
        "Exp3m"
    };
    write_results(result_matrix, metadata, descriptions, out_path);

}


template <typename Dataset>
void run_tsallis_experiment(Dataset d, int k, int rounds, int averages, double gap,
                            const std::string &out_path = "/tmp/out") {

    std::vector<double> exp3_regrets(rounds);
    std::vector<double> exp31_regrets(rounds);
    std::vector<double> ucb_exp3_regrets(rounds);
    std::vector<double> tsallis_iw_regrets(rounds);
    std::vector<double> tsallis_rv_regrets(rounds);

    std::vector<double> fpl_regrets(rounds);
    std::vector<double> ucb_fpl_regrets(rounds);
    std::vector<double> uniform_regrets(rounds);


    for (int i = 0; i < averages; i++) {
        std::vector<std::vector<double>> data_matrix = d.generate();
        Exp3 exp3(k, 0.1);

        TsallisIW iw;
        TsallisINF tsallis_iw(k, iw);
        TsallisRV rv;
        TsallisINF tsallis_rv(k, rv);

        Exp3 ucb_exp3_bandit(k, 0.1);
        UCB1 ucb_exp3(10, ucb_exp3_bandit);

        Uniformbandit uni(k);


        FPLVectorWeightStrategy fpl_ws(k);
        NaiveRandomGenStrategy fpl_rs(k, 10);
        FPL fpl(fpl_ws, fpl_rs);

        //FPL_weightless fpl(k, 0.9);

        FPLVectorWeightStrategy fpl_ucb_ws(k);
        NaiveRandomGenStrategy fpl_ucb_rs(k, 10);
        FPL ucb_fpl_bandit(fpl_ucb_ws, fpl_ucb_rs);
        UCB1 ucb_fpl(10, ucb_fpl_bandit);

        Exp31 exp31(k);


        std::vector<double> exp3_run;
        std::thread t1(basic_tsallis_runner<Exp3>, std::ref(exp3), std::ref(data_matrix), rounds, std::ref(exp3_run));

        std::vector<double> exp31_run;

        std::thread t2(basic_tsallis_runner<Exp31>, std::ref(exp31), std::ref(data_matrix), rounds,
                       std::ref(exp31_run));


        std::vector<double> fpl_run;
        //std::thread t3(basic_tsallis_runner<FPL<FPLVectorWeightStrategy, NaiveRandomGenStrategy>>, std::ref(fpl),
        std::thread t3(basic_tsallis_runner<FPL<FPLVectorWeightStrategy,NaiveRandomGenStrategy>>, std::ref(fpl),
                       std::ref(data_matrix), rounds, std::ref(fpl_run));

        std::vector<double> ucb_fpl_run;
        std::thread t4(basic_tsallis_runner<UCB1<FPL<FPLVectorWeightStrategy, NaiveRandomGenStrategy>>>,
                       std::ref(ucb_fpl), std::ref(data_matrix), rounds, std::ref(ucb_fpl_run));


        std::vector<double> tsallis_iw_run;
        std::thread t5(basic_tsallis_runner<TsallisINF<TsallisIW>>, std::ref(tsallis_iw), std::ref(data_matrix), rounds,
                       std::ref(tsallis_iw_run));

        std::vector<double> tsallis_rv_run;
        std::thread t6(basic_tsallis_runner<TsallisINF<TsallisRV>>, std::ref(tsallis_rv), std::ref(data_matrix), rounds,
                       std::ref(tsallis_rv_run));


        std::vector<double> ucb_exp3_run;
        std::thread t7(basic_tsallis_runner<UCB1<Exp3>>, std::ref(ucb_exp3), std::ref(data_matrix), rounds,
                       std::ref(ucb_exp3_run));

        std::vector<double> uniform_run;
        std::thread t8(basic_tsallis_runner<Uniformbandit>, std::ref(uni), std::ref(data_matrix), rounds,
                       std::ref(uniform_run));

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();

        for (int round = 0; round < rounds; round++) {
            exp3_regrets[round] += exp3_run[round];
            exp31_regrets[round] += exp31_run[round];
            fpl_regrets[round] += fpl_run[round];
            ucb_fpl_regrets[round] += ucb_fpl_run[round];
            tsallis_iw_regrets[round] += tsallis_iw_run[round];
            tsallis_rv_regrets[round] += tsallis_rv_run[round];
            ucb_exp3_regrets[round] += ucb_exp3_run[round];
            uniform_regrets[round] += uniform_run[round];

        }
    }

    for (auto &v: exp3_regrets) v /= averages;
    for (auto &v: exp31_regrets) v /= averages;
    for (auto &v: ucb_fpl_regrets) v /= averages;
    for (auto &v: fpl_regrets) v /= averages;
    for (auto &v: tsallis_iw_regrets) v /= averages;
    for (auto &v: tsallis_rv_regrets) v /= averages;
    for (auto &v: ucb_exp3_regrets) v /= averages;
    for (auto &v: uniform_regrets) v /= averages;


    std::vector<std::vector<double>> result_matrix;
    result_matrix.push_back(exp3_regrets);
    result_matrix.push_back(exp31_regrets);
    result_matrix.push_back(ucb_exp3_regrets);

    result_matrix.push_back(fpl_regrets);
    result_matrix.push_back(ucb_fpl_regrets);

    result_matrix.push_back(tsallis_iw_regrets);
    result_matrix.push_back(tsallis_rv_regrets);

    result_matrix.push_back(uniform_regrets);

    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
            description +
            std::to_string(k) + ","
            + std::to_string(rounds) + ","
            + std::to_string(gap) + ","
            + "Exp3,Exp3.1,UCB1 (Exp3),FPL,UCB (FPL),Tsallis-INF (IW),Tsallis-INF (RV),Uniform,";
    auto descriptions = std::vector<string>{
            "Exp3",
            "Exp3.1",
            "UCB1 (Exp3)",
            "FPL",
            "UCB (FPL)",
            "Tsallis-INF (IW)",
            "Tsallis-INF (RV)",
            "Uniform"
    };
    write_results(result_matrix, metadata, descriptions, out_path);
}

#endif //EFFICIENT_MULTI_ARMED_BANDITS_TSALLISEXPERIMENTRUNNER_H