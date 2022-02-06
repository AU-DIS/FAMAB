//
// Created by Mathias Ravn Tversted on 01/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H


#include <vector>
#include <random>
#include "IBandit.h"

class Exp3 : public IBandit {

public:
    Exp3(double gamma, int k);
    int draw() override;
    void give_reward(int choice, double reward) override;
private:
    double* weights_;
    std::vector<double> P_;
    int K_;
    double gamma_;
    int sample();
    std::mt19937 gen_;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H
