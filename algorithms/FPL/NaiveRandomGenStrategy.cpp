//
// Created by Kristoffer Strube on 14-02-2022.
//

#include "NaiveRandomGenStrategy.h"
#include "iostream"
#include "../../utilities/random_gen.h"


NaiveRandomGenStrategy::NaiveRandomGenStrategy(size_t k, double eta) : _k(k), _eta(eta) {
    _exponential_distribution = std::exponential_distribution<double>(_eta);
    _gen = random_gen();
}

std::vector<double> NaiveRandomGenStrategy::random_weights() {
    std::vector<double> random_doubles;
    for (size_t i = 0; i < _k; i++) {
        random_doubles.push_back(_exponential_distribution(_gen));
    }
    //std::cout << *std::max_element(random_doubles.begin(), random_doubles.end()) << std::endl;


    return random_doubles;
}