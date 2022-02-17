//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_STOCHASTIC_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_STOCHASTIC_H
#include <vector>

class debug_simple_stochastic {
public:
        explicit debug_simple_stochastic(int K, int number_to_sample);
        double feedback(int choice, double &regret);

        int k = 0;
        double reward_max = 1;
        double reward_min = 0;
        double min_regret = 0;
        double max_regret = 0;
        double max_possible_reward = 0;

    private:
        std::vector<double> _data_matrix;
    };

#endif //EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_STOCHASTIC_H