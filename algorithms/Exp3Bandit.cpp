//
// Created by Mathias Tversted on 06/02/2022.
//


#include "IWeightStrategy.h"
#include "IRewardStrategy.h"
#include "Exp3Bandit.h"
#include <iostream>

Exp3Bandit::Exp3Bandit(IWeightStrategy *ws, IRewardStrategy *rs) {
        _weightStrategy = ws;
        _rewardStrategy = rs;
    }

    int Exp3Bandit::choose()  {
        return _weightStrategy->choose();
    }
    void Exp3Bandit::give_reward(int index, double feedback)  {
        double reward = _rewardStrategy->reward(index, feedback);
        _weightStrategy->update_weight(index, reward);
    }

Exp3Bandit::~Exp3Bandit() {
    free(_weightStrategy);
    free(_rewardStrategy);
}

