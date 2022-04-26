//
// Created by Mathias Ravn Tversted on 01/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#include "vector"
#include "set"
#include <iostream>

template<typename Bandit, typename Dataset>
/// @param bandit The bandit to use
/// @param data Must implement reset(), feedback(int choice)
/// @param rounds Number of rounds
/// @returns vector of regrets
std::vector<double> basic_runner(Bandit &bandit, Dataset &data, int rounds){
    data.reset();
    std::vector<double> regrets;
    regrets.reserve(rounds);
    for (int round = 0; round < rounds; round++) {
        auto choice = bandit.choose();

        // Check out this shit
        // https://www.educative.io/edpresso/how-to-return-multiple-values-from-a-function-in-cpp17
        auto [feedback, regret] = data.feedback(choice);
        bandit.give_reward(choice, feedback);
        regrets.push_back(regret);
    }
    return regrets;
}

template <typename Bandit>
void basic_tsallis_runner(Bandit &bandit, std::vector<std::vector<double>> &data_matrix, int rounds, std::vector<double> &regrets){
    regrets.reserve(rounds);
    for (int round = 0; round < rounds; round++) {
        auto choice = bandit.choose();
        auto reward = data_matrix[choice][round];
        double max_element = 0;
        for (auto & arm : data_matrix) {
            if (arm[round] >= max_element) max_element = arm[round];
        }
        double regret = max_element - reward;
        bandit.give_reward(choice, reward);
        regrets.push_back(regret);
    }
}

template <typename Bandit>
void top_k_runner(Bandit &bandit, std::vector<std::vector<double>> &data_matrix, int rounds, int m, std::vector<double> &regrets){
    regrets.reserve(rounds);
    for (int round = 0; round < rounds; round++) {

        double round_regret = 0;

        std::set<int> k_set;
        while (k_set.size() < m) {
            int choice = bandit.choose();
            k_set.insert(choice);
        }
        std::set<int> taken;

        double max_regret = 0;
        double round_reward = 0;

        for (int i = 0; i < m; i++) {
            double max_element = 0;
            for (int arm = 0; arm < data_matrix.size(); arm++) {
                if (taken.count(arm) == 0 && data_matrix[arm][round] > max_element){
                    max_regret += data_matrix[arm][round];
                    taken.insert(arm);
                    break;
                }
            }
        }



        for (auto v : k_set) {
            double max_element = 0;
            for (int arm = 0; arm < data_matrix.size(); arm++) {
                if (taken.count(arm) == 0 && data_matrix[arm][round] > max_element){
                    max_element = data_matrix[arm][round];
                    taken.insert(arm);
                    break;
                }
            }
            auto reward = data_matrix[v][round];
            round_regret += reward;
            bandit.give_reward(v, reward);
        }

        round_regret = max_regret - round_reward;
        regrets.push_back(round_regret);
    }
}

template <typename Bandit>
void qbl_k_runner(Bandit &bandit, std::vector<std::vector<double>> &data_matrix, int rounds, int m, std::vector<double> &regrets){
    regrets.reserve(rounds);
    for (int round = 0; round < rounds; round++) {
        double round_regret = 0;

        std::set<int> taken;

        double max_regret = 0;
        double round_reward = 0;

        for (int i = 0; i < m; i++) {
            double max_element = 0;
            for (int arm = 0; arm < data_matrix.size(); arm++) {
                if (taken.count(arm) == 0 && data_matrix[arm][round] > max_element){
                    max_regret += data_matrix[arm][round];
                    taken.insert(arm);
                    break;
                }
            }
        }


        auto choices = bandit.choose(m);
        auto rewards = std::vector<double>();
        for (auto v : choices) {
            auto reward = data_matrix[v][round];
            rewards.push_back(reward);
            round_reward += reward;
        }
        round_regret = max_regret - round_reward;
        bandit.give_reward(choices, rewards);
        regrets.push_back(round_regret);
    }
}



#endif //EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
