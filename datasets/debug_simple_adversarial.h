//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#include "vector"
#include "random"
#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_ADVERSARIAL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_ADVERSARIAL_H


class debug_simple_adversarial {
public:
    debug_simple_adversarial(int K, int rounds);
    double feedback(int choice);
    int k = 0;
    int reward_max = 1;
    int reward_min = 0;
private:
    std::vector<double> _data_matrix;
    void randomize_weights();
    std::random_device _rd;
    std::mt19937 _gen;
    std::normal_distribution<double> _d;
    int _rounds = 0;
    int _current_round = 0;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_DEBUG_SIMPLE_ADVERSARIAL_H