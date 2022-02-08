//
// Created by Kristoffer Strube on 08-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_CPP


#include "IRewardStrategy.cpp"
#include "IWeightStrategy.cpp"
#include <math.h>

class Exp3RewardStrategy : public IRewardStrategy {
private:
    IWeightStrategy *_weightStrategy;
public:
    explicit Exp3RewardStrategy(IWeightStrategy *ws) {
        _weightStrategy = ws;
    }
    double reward(int index, double feedback) override {
        double estimated_reward = feedback/_weightStrategy->last_drawn_probability;
        return _weightStrategy->last_drawn_weight * exp((_weightStrategy->gamma * estimated_reward)/_weightStrategy->k);
    }
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_CPP