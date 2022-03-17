//
// Created by Kristoffer Strube on 08-02-2022.
//


#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3TORREWARDSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3TORREWARDSTRATEGY_H
#include "iostream"
#include "math.h"

template <typename WeightStrategy>
class Exp3TorRewardStrategy {
private:
    WeightStrategy &_weightStrategy;
    double _eta;
public:
    Exp3TorRewardStrategy(WeightStrategy &ws, double eta)
    :_weightStrategy(ws), _eta(eta)
    {

    }

    double estimated_reward(double feedback) {
        auto est =  feedback/_weightStrategy.last_drawn_probability;
        return est;
    }

    double estimated_loss(double feedback) {
        auto est = (1-feedback)/_weightStrategy.last_drawn_probability;
        return est;
    }

    double new_weight(double feedback) {
        double est_loss = estimated_loss(feedback);
        std::cout << "last_drawn_probability: " << std::to_string(_weightStrategy.last_drawn_probability) << std::endl;
        std::cout << "feedback: " << std::to_string(feedback) << std::endl;
        std::cout << "est_loss: " << std::to_string(est_loss) << std::endl;
        double v = _weightStrategy.last_drawn_weight * exp((-_eta * est_loss));
        return v;
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3TORREWARDSTRATEGY_H