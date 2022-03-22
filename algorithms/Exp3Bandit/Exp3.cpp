//
// Created by Kristoffer Strube on 22-03-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3_CPP

#include "Exp3.h"
#include <random>
#include <iostream>

Exp3::Exp3(int k, double gamma)
        : _k(k), _gamma(gamma) {
    _probabilities = std::vector<double>();
    for (int i = 0; i < k; i++) {
        _probabilities.push_back(0);
    }
    _weights = std::vector<double>();
    // Init all to 1
    for (int i = 0; i < k; i++) {
        _weights.push_back(1.0);
    }
};

int Exp3::sample() {
    std::discrete_distribution<int> d(_probabilities.begin(), _probabilities.end());
    int s = d(_random_gen);
    return s;
}

int Exp3::choose() {
    double sum_wj = 0;
    for (int i = 0; i < _k; i++) {
        sum_wj += _weights[i];
    }

    for (int i = 0; i < _k; i++) {
        _probabilities[i] = (1 - _gamma) * (_weights[i] / sum_wj) + _gamma / _k;
    }

    int choice = sample();
    _last_drawn_probability = _probabilities[choice];
    _last_drawn_weight = _weights[choice];

    return choice;
}

void Exp3::give_reward(int index, double feedback) {
    double est_reward = feedback / _last_drawn_probability;
    double new_weight = _last_drawn_weight * exp((_gamma * est_reward) / _k);
    _weights[index] = new_weight;
}


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3_CPP
