//
// Created by Mathias Ravn Tversted on 17/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H
#include <math.h>
#include <vector>
#include <random>
#include "../../utilities/random_gen.h"

class Exp31 {
private:
    int _k;
    int _r;
    int _g_r;
    double _gamma;
    double _last_drawn_weight;
    double _last_drawn_probability;

    std::vector<double> _probabilities;
    std::mt19937 _random_gen = random_gen();
    std::vector<double> accumulated_rewards;
    int sample();
public:
    Exp31(int k);
    int choose();
    void give_reward(int index, double feedback);
    std::vector<double> _weights;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H