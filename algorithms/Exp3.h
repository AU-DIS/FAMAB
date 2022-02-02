//
// Created by Mathias Ravn Tversted on 01/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H


#include <vector>
#include <random>

class Exp3 {

public:
    Exp3(double gamma, int k);
    int draw();
    void give_reward(int choice, double reward);
private:
    double* weights_;
    std::vector<double> P_;
    int K_;
    double gamma_;
    int sample();
    std::random_device rd_;
    std::mt19937 gen_;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H
