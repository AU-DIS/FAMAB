//
// Created by Kristoffer Strube on 14-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPLVECTORWEIGHTSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPLVECTORWEIGHTSTRATEGY_H

#include <vector>
#include <random>

class FPLVectorWeightStrategy {
private:
    int _k;
public:
    std::vector<double> _weights;
    explicit FPLVectorWeightStrategy(size_t k);
    void add_to_weight(size_t i, double weight);
    void add_to_weights(std::vector<double> vector);
    int max_weight();

    std::vector<double> get_weights();
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_FPLVECTORWEIGHTSTRATEGY_H
