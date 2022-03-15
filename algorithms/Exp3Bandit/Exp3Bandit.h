//
// Created by Mathias Ravn Tversted on 10/02/2022.
//


#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H
#include <math.h>

template<typename WeightStrategy, typename RewardStrategy>
class Exp3Bandit {
private:
    RewardStrategy _rewardStrategy;
public:
    WeightStrategy _weightStrategy;

    Exp3Bandit(WeightStrategy &ws, RewardStrategy &rs)
    :_weightStrategy(ws), _rewardStrategy(rs){}

    Exp3Bandit(const Exp3Bandit &b)
    :_weightStrategy(b._weightStrategy), _rewardStrategy(_weightStrategy) {

    }

    int choose() {
        return _weightStrategy.choose();
    }

    void give_reward(size_t index, double feedback) {
        auto new_weight = _rewardStrategy.new_weight(feedback);
        _weightStrategy.update_weight(index, new_weight);
    }
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H
