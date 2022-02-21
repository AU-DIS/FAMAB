//
// Created by Mathias Ravn Tversted on 19/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP31M_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP31M_H

#include <vector>
#include "algorithm"
#include "iostream"
#include "../../utilities/argsort.h"

template<typename Exp3m>
class Exp31m {

public:
    Exp31m(int K, int k, Exp3m b) : _K(K), _k(k), b(b) {
        g_r = (_K * log(_K))/(exp(1)-1)*pow(4, _r);
        gamma = std::min(1.0, sqrt(_K * log(_K))/(exp(1) - 1)*g_r);
        _r += 1;

        for (int i = 0; i < _K; i++) accumulated_rewards.push_back(0);
    };

    std::vector<int> choose() {
            g_r = (_K * log(_K)) / (exp(1) - 1) * pow(4, _r);
            auto g_max = *std::max_element(accumulated_rewards.begin(), accumulated_rewards.end());
            if (g_max > (g_r - _K / gamma)) {
                gamma = std::min(1.0, sqrt(_K * log(_K)) / (exp(1) - 1) * g_r);
                b._gamma = gamma;
                _r += 1;
            }
            return b.choose();
    };


    void give_reward(std::vector<int> &indices, std::vector<double> &rewards) {

            for (int i = 0; i < indices.size(); i++ ) {
                int index = indices[i];
                accumulated_rewards[index] += rewards[i]/b._last_probabilities[index];
            }
            b.give_reward(indices, rewards);
    }

private:
    int _K;
    int _k;
    int _r = 0;
    Exp3m b;
    int g_r = 0;
    std::vector<double> accumulated_rewards;
    double gamma;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP31M_H
