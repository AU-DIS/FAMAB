//
// Created by Mathias Ravn Tversted on 15/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_TSALLISEXPERIMENTRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_TSALLISEXPERIMENTRUNNER_H
#include <thread>

void run_tsallis_experiment(std::vector<std::vector<double>> &data_matrix, int k, int rounds, int averages, double gap, const std::string& out_path="/tmp/out") {
    Exp3 exp3(k, 0.25);

    TsallisIW iw;
    TsallisINF tsallis_iw(k, iw);
    TsallisRV rv;
    TsallisINF tsallis_rv(k, rv);

    Exp3 ucb_exp3_bandit(k, 0.1);
    UCB1 ucb_exp3(10, ucb_exp3_bandit);

    Uniformbandit uni(k);

    FPLVectorWeightStrategy fpl_ws(k);
    NaiveRandomGenStrategy fpl_rs(k, 0.2);
    FPL fpl(fpl_ws, fpl_rs);

    FPLVectorWeightStrategy fpl_ucb_ws(k);
    NaiveRandomGenStrategy fpl_ucb_rs(k, 0.2);
    FPL ucb_fpl_bandit(fpl_ucb_ws, fpl_ucb_rs);
    UCB1 ucb_fpl(10, ucb_fpl_bandit);

    Exp31 exp31(k);


    std::vector<double> exp3_regrets(rounds);
    std::vector<double> exp31_regrets(rounds);
    std::vector<double> ucb_exp3_regrets(rounds);
    std::vector<double> tsallis_iw_regrets(rounds);
    std::vector<double> tsallis_rv_regrets(rounds);

    std::vector<double> fpl_regrets(rounds);
    std::vector<double> ucb_fpl_regrets(rounds);
    std::vector<double> uniform_regrets(rounds);


    for (int i = 0; i < averages; i++) {
        std::vector<double> exp3_run;
        std::thread t1(basic_tsallis_runner<Exp3>, std::ref(exp3), std::ref(data_matrix), rounds, std::ref(exp3_run));

        std::vector<double> exp31_run;

        std::thread t2(basic_tsallis_runner<Exp31>, std::ref(exp31), std::ref(data_matrix), rounds, std::ref(exp31_run));


        std::vector<double> fpl_run;
        std::thread t3(basic_tsallis_runner<FPL<FPLVectorWeightStrategy, NaiveRandomGenStrategy>>, std::ref(fpl), std::ref(data_matrix), rounds, std::ref(fpl_run));

        std::vector<double> ucb_fpl_run;
        std::thread t4(basic_tsallis_runner<UCB1<FPL<FPLVectorWeightStrategy, NaiveRandomGenStrategy>>>, std::ref(ucb_fpl), std::ref(data_matrix), rounds, std::ref(ucb_fpl_run));


        std::vector<double> tsallis_iw_run;
        std::thread t5(basic_tsallis_runner<TsallisINF<TsallisIW>>, std::ref(tsallis_iw), std::ref(data_matrix), rounds, std::ref(tsallis_iw_run));

        std::vector<double> tsallis_rv_run;
        std::thread t6(basic_tsallis_runner<TsallisINF<TsallisRV>>, std::ref(tsallis_rv), std::ref(data_matrix), rounds, std::ref(tsallis_rv_run));


        std::vector<double> ucb_exp3_run;
        std::thread t7(basic_tsallis_runner<UCB1<Exp3>>, std::ref(ucb_exp3), std::ref(data_matrix), rounds, std::ref(ucb_exp3_run));

        std::vector<double> uniform_run;
        std::thread t8(basic_tsallis_runner<Uniformbandit>, std::ref(uni), std::ref(data_matrix), rounds, std::ref(uniform_run));

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
    for (auto &v : exp31_regrets) v /= averages;
    for (auto &v : ucb_fpl_regrets) v /= averages;
    for (auto &v : fpl_regrets) v /= averages;
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


std::vector<std::discrete_distribution<int>> create_distributions(int k) {
    std::vector<std::discrete_distribution<int>> distributions(k);

    std::normal_distribution<double> gamma_distribution(1.2, 1);


    auto gen = random_gen();

    std::vector<double> probabilities(k);
    for (int i = 0; i < k; i++) {
        double p = gamma_distribution(gen);
        probabilities[i] = p;
    }

    double max_p = *std::max_element(probabilities.begin(), probabilities.end());
    double min_p = *std::min_element(probabilities.begin(), probabilities.end());

    for (int i = 0; i < k; i++) {
        probabilities[i] += min_p;
        probabilities[i] /= (max_p + min_p);
        std::vector<double> weights = {probabilities[i], 1. - probabilities[i]};
        std::discrete_distribution<int> dist(weights.begin(), weights.end());
        distributions[i] = dist;
    }
    return distributions;
}


std::vector<std::discrete_distribution<int>> create_distributions(int k, int optimal_start, int optimal_end, double delta) {
    std::vector<std::discrete_distribution<int>> distributions(k);
    auto gen = random_gen();

    std::normal_distribution<double> suboptimal_distribution(1  - delta, 4);
    std::discrete_distribution<int> optimal_distribution({1 - delta, delta});

    std::vector<double> probabilities(k);

    std::vector<double*> suboptimal_probabilities;

    for (int i = 0; i < k; i++) {
        if (i >= optimal_start && i <= optimal_end) {
            probabilities[i] = delta;
        }
        else {
            double p = suboptimal_distribution(gen);
            probabilities[i] = p;
            suboptimal_probabilities.push_back(&p);
        }
    }

    double max_p = 0;
    double min_p = k + 1;
    for (double *p : suboptimal_probabilities) {
        if (*p < min_p) min_p = *p;
        else if (*p >= max_p) max_p = *p;
    }
    for (double *p : suboptimal_probabilities) {
        *p /= (min_p + max_p);
    }

    for (int i = 0; i < k; i++) {
        std::vector<double> weights = {1 - probabilities[i], probabilities[i]};
        std::discrete_distribution<int> dist(weights.begin(), weights.end());
        distributions[i] = dist;
    }

    return distributions;
}


std::vector<std::vector<double>> adversarial_with_gap(int k, int rounds, double gap, double delta) {
    auto gen = random_gen();
    std::vector<std::vector<double>> data_matrix;
    data_matrix.reserve(k);


    auto distributions = create_distributions(k, 0, int(pow(gap, 1)), delta);
    for (int i = 0; i < k; i++) {
        std::vector<double> row(rounds, 1);
        data_matrix.push_back(row);
    }
    bool even = true;


    int multiple = 1;
    for (int i = 0; i < rounds; i++) {
        double threshold = pow(gap, multiple);
        if (i > threshold) {
            int interval_end = (int) pow(gap, multiple+1);
            distributions = create_distributions(k, (int) pow(gap, multiple), interval_end <= k ? interval_end : k, delta);
            even = !even;
            multiple++;
        }

        for (int arm = 0; arm < k; arm++) {
            data_matrix[arm][i] = distributions[arm](gen);
            // Outcomment to enable weight mod 2 switching
            //data_matrix[arm][i] = even ? arm % 2 : (arm+1) % 2;
        }
    }

    return data_matrix;
}




std::vector<std::vector<double>> stochastically_constrained_adversarial(int k, double delta, int rounds, double gap) {
    auto gen = random_gen();


    std::discrete_distribution<int> first_optimal({0, 1});
    std::discrete_distribution<int> first_suboptimal( {1 - delta, delta});

    std::discrete_distribution<int> second_optimal({1 - delta, delta});
    std::discrete_distribution<int> second_suboptimal({0, 1});


    auto arm_picker_weights = std::vector<int>(k, 1);
    std::discrete_distribution<int> optimal_arm_picker(arm_picker_weights.begin(), arm_picker_weights.end());


    std::vector<std::vector<double>> data_matrix;
    data_matrix.reserve(k);

    for (int i = 0; i < k; i++) {
        std::vector<double> row(rounds);
        data_matrix.push_back(row);
    }

    auto current_optimal = first_optimal;
    auto current_suboptimal = first_optimal;
    auto is_first = true;
    int multiple = 1;
    int optimal_arm = 1;
    for (int round = 0; round < rounds; round ++) {
        double threshold = pow(gap, multiple);
        if (round > threshold) {
            optimal_arm = optimal_arm_picker(gen);
            current_optimal = is_first ? second_optimal : first_optimal;
            current_suboptimal = is_first ? second_suboptimal : second_optimal;
            is_first = !is_first;
            multiple++;
        }

        for (int arm = 0; arm < k; arm++) {
            data_matrix[arm][round] = current_suboptimal(gen);
        }
        data_matrix[optimal_arm][round] = current_optimal(gen);
    }
    return data_matrix;
}


#endif //EFFICIENT_MULTI_ARMED_BANDITS_TSALLISEXPERIMENTRUNNER_H