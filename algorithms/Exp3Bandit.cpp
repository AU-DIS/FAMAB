//
// Created by Mathias Tversted on 06/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_CPP


#include "IWeightStrategy.cpp"
#include "IRewardStrategy.cpp"
#include <iostream>

class Exp3Bandit {
public:
    Exp3Bandit(IWeightStrategy *ws, IRewardStrategy *rs) {
        weightStrategy = ws;
        rewardStrategy = rs;
    }
    [[nodiscard]] int choose() const {
        return weightStrategy->choose();
    }
    void give_reward(int index, double feedback) const {
        double reward = rewardStrategy->reward(index, feedback);
        weightStrategy->update_weight(index, reward);
    }
    IWeightStrategy *weightStrategy;
    IRewardStrategy *rewardStrategy;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_CPP
