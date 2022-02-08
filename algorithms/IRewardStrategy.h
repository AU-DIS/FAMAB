//
// Created by hhhha on 08-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_IREWARDSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_IREWARDSTRATEGY_H

class IRewardStrategy {
public:
    virtual double reward(int index);
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_IREWARDSTRATEGY_H
