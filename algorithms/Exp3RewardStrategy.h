//
// Created by Kristoffer Strube on 08-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_H


#include "IRewardStrategy.h"
#include "IWeightStrategy.h"

class Exp3RewardStrategy : public IRewardStrategy {
private:
    IWeightStrategy *_weightStrategy;
public:
    explicit Exp3RewardStrategy(IWeightStrategy *ws);
    double reward(int index, double feedback) override;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3REWARDSTRATEGY_H
