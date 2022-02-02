//
// Created by Mathias Ravn Tversted on 01/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H


#include <vector>

class Exp3 {

public:
    Exp3(double gamma, int k);
    int draw();
    void give_reward(int choice, double reward);
private:
    double* weights;
    std::vector<double> P;
    int K{};
    double gamma{};
    int sample();
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3_H
