//
// Created by Mathias Tversted on 05/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#include <vector>
#include <random>

class FPL {
public:
    FPL(double eta, int K);
    int draw();
    void give_reward(int choice, double reward);
private:
    void perturb_weights();
    std::vector<double> weights_;
    int K_;
    double eta_;
    std::random_device rd_;
    std::mt19937 gen_;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
