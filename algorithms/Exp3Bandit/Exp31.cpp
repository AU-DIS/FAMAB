//
// Created by Kristoffer Strube on 22-03-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP31_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP31_CPP

#include <cmath>
#include "vector"
#include <random>
#include "Exp31.h"
#include <iostream>

Exp31::Exp31(int k) : _k(k) {
    for (int i = 0; i < _k; i++) {
        accumulated_rewards.push_back(0);
        _probabilities.push_back(1./k);
        _weights.push_back(1);
    }

    _g_r = (_k * log(_k)) / (exp(1) - 1) * pow(4, _r);
    double gamma = std::min(1.0, sqrt(_k * log(_k)) / (exp(1) - 1) * _g_r);
    _gamma = gamma;
    _r += 1;
}

int Exp31::sample() {
    std::discrete_distribution<int> d(_probabilities.begin(), _probabilities.end());
    int s = d(_random_gen);
    return s;
}

int Exp31::choose() {
    _g_r = (_k * log(_k)) / (exp(1) - 1) * pow(4, _r);
    auto g_max = *std::max_element(accumulated_rewards.begin(), accumulated_rewards.end());
    if (g_max > (_g_r - _k / _gamma)) {
        double gamma = std::min(1.0, sqrt(_k * log(_k)) / (exp(1) - 1) * _g_r);
        _gamma = gamma;
        _r += 1;
    }

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

void Exp31::give_reward(int index, double feedback) {
    double est_reward = feedback / _last_drawn_probability;
    accumulated_rewards[index] += est_reward;
    double new_weight = _last_drawn_weight * exp((_gamma * est_reward) / _k);
    _weights[index] = new_weight;
}

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP31_CPP