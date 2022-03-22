//
// Created by Kristoffer Strube on 22-03-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_CPP

#include "Exp3Tor.h"
#include <random>
#include <iostream>

Exp3Tor::Exp3Tor(int k, double eta)
        : _k(k), _eta(eta) {
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

int Exp3Tor::sample() {
    std::discrete_distribution<int> d(_probabilities.begin(), _probabilities.end());
    int s = d(_random_gen);
    return s;
}

int Exp3Tor::choose() {
    double sum_wj = 0;
    for (int i = 0; i < _k; i++) {
        sum_wj += _weights[i];
    }

    for (int i = 0; i < _k; i++) {
        _probabilities[i] = (_weights[i] / sum_wj);
    }

    int choice = sample();
    _last_drawn_probability = _probabilities[choice];
    _last_drawn_weight = _weights[choice];

    return choice;
}

void Exp3Tor::give_reward(int index, double feedback) {
    double est_loss = (1-feedback)/_last_drawn_probability;
    double new_weight = _last_drawn_weight * exp((-_eta * est_loss));
    _weights[index] = new_weight;
}


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_CPP
