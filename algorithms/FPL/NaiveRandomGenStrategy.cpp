//
// Created by Kristoffer Strube on 14-02-2022.
//

#include "NaiveRandomGenStrategy.h"


NaiveRandomGenStrategy::NaiveRandomGenStrategy(size_t k, double eta) : _k(k), _eta(eta) {
    _exponential_distribution = std::exponential_distribution<double>(_eta);
}

std::vector<double> NaiveRandomGenStrategy::random_weights() {
    std::vector<double> randomDoubles(_k);
    for (size_t i = 0; i < _k; i++) {
        randomDoubles.push_back(_exponential_distribution(_gen));
    }
    return randomDoubles;
}