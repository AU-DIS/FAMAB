//
// Created by Mathias Ravn Tversted on 01/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#include "vector"

template<typename Bandit, typename Dataset>
static std::vector<std::vector<double>> runner(std::vector<Bandit> bandits, Dataset data, int rounds, std::string metadata, std::vector<std::string> &descriptions){
    std::vector<std::vector<double>> regret_matrix;
    for (int bandit_index = 0; i < bandits.size(); bandit_index++) {
        std::vector<double> round_regrets;

        auto bandit = bandits[bandit_index];
        for (int round = 0; round < rounds; round++) {
            data.reset();
            auto choice = bandit.choose();
            // Check out this shit
            // https://www.educative.io/edpresso/how-to-return-multiple-values-from-a-function-in-cpp17
            auto [feedback, regret] = data.feedback(choice);
            bandit.give_reward(choice, feedback);
            round_regrets.push_back(regret);
        }
        regret_matrix.push_back(round_regrets);
    }
    return regret_matrix;
}

#endif //EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
