//
// Created by Mathias Tversted on 05/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#include <vector>
#include <random>

template<typename WeightStrategy, typename RandomGenStrategy>
class FPL {
private:
    WeightStrategy &_weightStrategy;
    RandomGenStrategy &_randomGenStrategy;
public:
    FPL(WeightStrategy &ws, RandomGenStrategy &rgs)
    :_weightStrategy(ws), _randomGenStrategy(rgs)
    {
    }
    int choose() {
        std::vector<double> random_weights = _randomGenStrategy.random_weights();

        _weightStrategy.add_to_weights(random_weights);

        return _weightStrategy.max_weight();
    }
    void give_reward(size_t choice, double feedback) {
        _weightStrategy.add_to_weight(choice, feedback);
    }
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_FPL_H