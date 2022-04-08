//
// Created by Mathias Ravn Tversted on 09/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_UNIFORMBANDIT_H
#define EFFICIENT_MULTI_ARMED_BANDITS_UNIFORMBANDIT_H
#include "random"
#include "../utilities/random_gen.h"

class Uniformbandit {
private:
    std::vector<double> uniform_weights;
    std::mt19937 gen = random_gen();

public:
    Uniformbandit(int K) {
        for (int i = 0; i < K; i++) uniform_weights.push_back(1.0/K);

    }
    int choose() {
        std::discrete_distribution<int> d(uniform_weights.begin(), uniform_weights.end());
        return d(gen);
    }
    void give_reward(int index, double feedback) {
        //HAH! Bamboozled;
    }

};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_UNIFORMBANDIT_H
