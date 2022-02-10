//
// Created by Kristoffer Strube on 08-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_IWEIGHTSTRATEGY_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_IWEIGHTSTRATEGY_CPP

#include <vector>

class IWeightStrategy {
public:
    virtual int choose() = 0;
    virtual void update_weight(int index, double weight) {};
    virtual std::vector<double> get_weights() = 0;
    int k{};
    double gamma{};
    double last_drawn_probability{};
    double last_drawn_weight{};
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_IWEIGHTSTRATEGY_CPP