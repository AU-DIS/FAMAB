//
// Created by Mathias Ravn Tversted on 17/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H

#include <cmath>
#include "vector"

template<typename WeightStrategy, typename RewardStrategy>
class Exp31 {
public:
    Exp31(WeightStrategy &ws, RewardStrategy &rs)
    :_weightStrategy(ws), _rewardStrategy(rs)
    {
        _K = _weightStrategy._k;
        for (int i = 0; i < _K; i++) {
            accumulated_rewards.push_back(0);
        }
        g_r = (_K * log(_K))/(exp(1)-1)*pow(4, _r);
        double gamma = std::min(1.0, sqrt(_K * log(_K))/(exp(1) - 1)*g_r);
        _weightStrategy._gamma = gamma;
        _r += 1;
    }
    int choose() {
        g_r = (_K * log(_K))/(exp(1)-1)*pow(4, _r);
        auto g_max = *std::max_element(accumulated_rewards.begin(), accumulated_rewards.end());
        if (g_max > (g_r - _K/_weightStrategy._gamma)) {
            double gamma = std::min(1.0, sqrt(_K * log(_K))/(exp(1) - 1)*g_r);
            _weightStrategy._gamma = gamma;
            _r += 1;
        }

        return _weightStrategy.choose();
    };

    void give_reward(int index, double feedback) {
        auto estimated_reward = _rewardStrategy.estimated_reward(index, feedback);
        accumulated_rewards[index] += estimated_reward;
        auto reward = _rewardStrategy.reward(index, feedback);
        _weightStrategy.update_weight(index, reward);
    }
    WeightStrategy &_weightStrategy;
    RewardStrategy &_rewardStrategy;
private:
    int _r = 0;
    int _K = 0;
    std::vector<double> accumulated_rewards;
    int g_r = 0;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H