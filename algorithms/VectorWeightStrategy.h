//
// Created by Mathias Ravn Tversted on 10/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H
#include <vector>
#include <random>
#include "IWeightStrategy.h"


class VectorWeightStrategy : public IWeightStrategy {
private:
    int sample();
    std::vector<double> _weights;
    std::vector<double> _probabilities;
    std::mt19937 _random_gen;
public:
    VectorWeightStrategy(int k, double gamma);
    int choose() override;
    void update_weight(int index, double weight) override;
    std::vector<double> get_weights() override;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H
