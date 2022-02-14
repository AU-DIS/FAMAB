//
// Created by Kristoffer Strube on 14-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H

#include <vector>
#include <random>

class VectorWeightStrategy {
private:
    int _k;
    std::vector<double> _weights;
public:
    explicit VectorWeightStrategy(size_t k);
    void add_to_weight(size_t i, double weight);
    void add_to_weights(std::vector<double> vector);
    int max_weight();
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H
