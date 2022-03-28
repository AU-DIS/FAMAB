//
// Created by Mathias Ravn Tversted on 01/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#include "vector"
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


#endif //EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
