//
// Created by Kristoffer Strube on 14-02-2022.
//

#include "NaiveRandomGenStrategy.h"
#include "iostream"


NaiveRandomGenStrategy::NaiveRandomGenStrategy(size_t k, double eta) : _k(k), _eta(eta) {
    _exponential_distribution = std::exponential_distribution<double>(_eta);
}

std::vector<double> NaiveRandomGenStrategy::random_weights() {
    std::vector<double> random_doubles;
    for (size_t i = 0; i < _k; i++) {
        random_doubles.push_back(_exponential_distribution(_gen));
    }
    auto max_element = *std::max_element(random_doubles.begin(), random_doubles.end());
    for (auto &v : random_doubles) v /= max_element;
    return random_doubles;
}