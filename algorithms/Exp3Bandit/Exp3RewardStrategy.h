//
// Created by Kristoffer Strube on 08-02-2022.
//


#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_H
#include "iostream"
#include "math.h"

template <typename WeightStrategy>
class Exp3RewardStrategy {

public:
    explicit Exp3RewardStrategy(WeightStrategy &ws)
    :_weightStrategy(ws)
    {

    }
    double estimated_reward(double feedback) {
        auto est =  feedback/_weightStrategy.last_drawn_probability;
        return est;
    }

    double new_weight(double feedback) {
        double est_reward = estimated_reward(feedback);
        double v =  _weightStrategy.last_drawn_weight * exp((_weightStrategy._gamma * est_reward)/_weightStrategy._k);
        return v;
    }
private:
    WeightStrategy &_weightStrategy;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_H