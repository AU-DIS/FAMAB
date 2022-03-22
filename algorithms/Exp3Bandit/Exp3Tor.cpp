//
// Created by Kristoffer Strube on 22-03-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_CPP

#include "Exp3Tor.h"
#include <random>
#include <iostream>
#include <cmath>

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
    double sum_reduced_power_weights = 0;
    double m = *max_element(_weights.begin(), _weights.end());
    for (int i = 0; i < _k; i++) {
        sum_reduced_power_weights += exp(_eta * _weights[i] - _eta * m);
    }

    for (int i = 0; i < _k; i++) {
        _probabilities[i] = exp(_eta * _weights[i] - _eta * m - log(sum_reduced_power_weights));
    }

    int choice = sample();

    return choice;
}

void Exp3Tor::give_reward(int index, double feedback) {
    for (int i = 0; i < _k; i++) {
        double est_loss = i == index ? (1 - feedback) / _probabilities[i] : 0;
        _weights[index] = _weights[index] + 1 - est_loss;
        if (std::isinf(_weights[index])) {
            std::cout << "INF!" << std::endl;
        }
    }
}


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_CPP
