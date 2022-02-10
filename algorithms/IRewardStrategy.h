//
// Created by Kristoffer Strube on 08-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_IREWARDSTRATEGY_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_IREWARDSTRATEGY_CPP

class IRewardStrategy {
public:
    virtual double reward(int index, double feedback) = 0;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_IREWARDSTRATEGY_CPP