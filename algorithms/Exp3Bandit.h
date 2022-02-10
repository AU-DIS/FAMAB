//
// Created by Mathias Ravn Tversted on 10/02/2022.
//


#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H

#include "IWeightStrategy.h"
#include "IRewardStrategy.h"

class Exp3Bandit {
public:
    Exp3Bandit(IWeightStrategy *ws, IRewardStrategy *rs);
    int choose();
    void give_reward(int index, double feedback);

    virtual ~Exp3Bandit();


private:
    IWeightStrategy *_weightStrategy;
    IRewardStrategy *_rewardStrategy;

};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H
