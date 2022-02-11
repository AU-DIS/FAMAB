//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_STOCHASTIC_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_STOCHASTIC_H
#include <vector>

class debug_simple_stochastic {
public:
        explicit debug_simple_stochastic(int K);
        double feedback(int choice);
    int k = 0;
        int reward_max = 1;
        int reward_min = 0;

    private:
        std::vector<double> _data_matrix;
    };

#endif //EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_STOCHASTIC_H
