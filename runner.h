//
// Created by Mathias Ravn Tversted on 01/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
#include "vector"

template<typename Bandit, typename Dataset>
/// @param bandit The bandit to use
/// @param data Must implement reset(), feedback(int choice)
/// @param rounds Number of rounds
/// @returns vector of regrets
static std::vector<double> runner(Bandit &bandit, Dataset &data, int rounds){
        data.reset();
        std::vector<double> regrets;
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

#endif //EFFICIENT_MULTI_ARMED_BANDITS_RUNNER_H
