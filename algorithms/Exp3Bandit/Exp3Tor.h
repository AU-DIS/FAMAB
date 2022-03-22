//
// Created by Mathias Ravn Tversted on 10/02/2022.
//


#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_H
#include <math.h>
#include <vector>
#include <random>
#include "../../utilities/random_gen.h"

class Exp3Tor {
private:
    int _k;
    double _eta;
    double _last_drawn_weight;
    double _last_drawn_probability;
    std::vector<double> _weights;
    std::vector<double> _probabilities;
    std::mt19937 _random_gen = random_gen();
    int sample();
public:
    Exp3Tor(int k, double eta);
    int choose();
    void give_reward(int index, double feedback);
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3TOR_H
