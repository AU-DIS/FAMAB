//
// Created by Mathias Ravn Tversted on 10/02/2022.
//


#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H


template<typename WeightStrategy, typename RewardStrategy>
class Exp3Bandit {
private:
    WeightStrategy &_weightStrategy;
    RewardStrategy &_rewardStrategy;
public:
    Exp3Bandit(WeightStrategy &ws, RewardStrategy &rs)
    :_weightStrategy(ws), _rewardStrategy(rs)
    {
    }

    int choose() {
        return _weightStrategy.choose();
    }

    void give_reward(size_t index, double feedback) {
        auto reward = _rewardStrategy.reward(index, feedback);
        _weightStrategy.update_weight(index, reward);
    }
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3BANDIT_H