//
// Created by Kristoffer Strube on 08-02-2022.
//


#include <vector>
#include <random>
#include "Exp3VectorWeightStrategy.h"
#include <iostream>


Exp3VectorWeightStrategy::Exp3VectorWeightStrategy(size_t k, double gamma) : _k(k), _gamma(gamma) {
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



int Exp3VectorWeightStrategy::sample() {
    std::discrete_distribution<int> d(_probabilities.begin(), _probabilities.end());
    int s =  d(_random_gen);
    std::cout << "s: " << std::to_string(s) << std::endl;
    return s;
}

int Exp3VectorWeightStrategy::choose() {
    double sum_wj = 0;
    for (int i = 0; i < _k; i++) {
        sum_wj += _weights[i];
    }

    for (int i = 0; i < _k; i++) {
        _probabilities[i] = (1 - _gamma) * (_weights[i] / sum_wj) + _gamma / _k;
    }

    int choice = sample();
    std::cout << "last_drawn_probability: " << std::to_string(_probabilities[choice]) << std::endl;
    last_drawn_probability = _probabilities[choice];
    last_drawn_weight = _weights[choice];

    return choice;
}

void Exp3VectorWeightStrategy::update_weight(size_t index, double weight) {
    _weights[index] = weight;
}

std::vector<double> Exp3VectorWeightStrategy::get_weights() {
    return _weights;
}



