//
// Created by Kristoffer Strube on 08-02-2022.
//


#include "Exp3RewardStrategy.h"
#include "IWeightStrategy.h"
#include <math.h>

Exp3RewardStrategy::Exp3RewardStrategy(IWeightStrategy * ws) {
    _weightStrategy = ws;
}

double Exp3RewardStrategy::reward(int index, double feedback) {
    double estimated_reward = feedback/_weightStrategy->last_drawn_probability;
    return _weightStrategy->last_drawn_weight * exp((_weightStrategy->gamma * estimated_reward)/_weightStrategy->k);
}

