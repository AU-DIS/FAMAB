//
// Created by Kristoffer Strube on 14-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_NAIVERANDOMGENSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_NAIVERANDOMGENSTRATEGY_H

#include <vector>
#include <random>

class NaiveRandomGenStrategy {
private:
    std::exponential_distribution<double> _exponential_distribution;
    std::mt19937 _gen;
    size_t _k;
    double _eta;
public:
    explicit NaiveRandomGenStrategy(size_t k, double eta);
    std::vector<double> random_weights();
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_NAIVERANDOMGENSTRATEGY_H
