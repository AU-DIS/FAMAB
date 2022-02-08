//
// Created by Mathias Tversted on 06/02/2022.
//

#include "IWeightStrategy.h"
#include "IRewardStrategy.h"

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_CPP

class Exp3Bandit {
public:
    Exp3Bandit(IWeightStrategy ws, IRewardStrategy rs) {

    }
    IWeightStrategy weightStrategy;
    IRewardStrategy rewardStrategy;
    int choose() {
        return weightStrategy.choose();
    }
    int give_reward(int index) {
        double reward = rewardStrategy.reward(index);
        weightStrategy.UpdateWeight(index, reward);
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_CPP
