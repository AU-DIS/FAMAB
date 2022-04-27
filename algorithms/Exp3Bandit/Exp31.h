//
// Created by Mathias Ravn Tversted on 17/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H
#include <math.h>
#include <vector>
#include <random>
#include "../../utilities/random_gen.h"
#include "Exp3.h"

class Exp31 {
private:
    int _k;
    int _r;
    double _g_r;
    double _gamma;

    std::vector<double> accumulated_rewards;
    Exp3 _exp3;
public:
    explicit Exp31(int k);
    int choose();
    void give_reward(int index, double feedback);
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP31_H