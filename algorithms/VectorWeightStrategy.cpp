//
// Created by Kristoffer Strube on 08-02-2022.
//


#include <vector>
#include <random>
#include "VectorWeightStrategy.h"
#include <iostream>


VectorWeightStrategy::VectorWeightStrategy(int k, double gamma) {
    _k = k;
    _gamma = gamma;

    _probabilities = std::vector<double>();
    for (int i = 0; i < k; i++) {
        _probabilities.push_back(0);
    }
    _weights = std::vector<double>();
    // Init all to 0
    for (int i = 0; i < k; i++) {
        _weights.push_back(1);
    }
};

int VectorWeightStrategy::sample() {
    std::discrete_distribution<> d(_probabilities.begin(), _probabilities.end());
    int s =  d(_random_gen);
    return s;
}

int VectorWeightStrategy::choose() {
    double sum_wj = 0;
    for (int i = 0; i < _k; i++) {
        sum_wj += _weights[i];
    }

    for (int i = 0; i < _k; i++) {
        _probabilities[i] = (1 - _gamma) * (_weights[i] / sum_wj) + _gamma / _k;
    }

    int choice = sample();
    last_drawn_probability = _probabilities[choice];
    last_drawn_weight = _weights[choice];
    return choice;
}

void VectorWeightStrategy::update_weight(int index, double weight) {
    _weights[index] = weight;
}

std::vector<double> VectorWeightStrategy::get_weights() {
    return _weights;
}


