//
// Created by Mathias Tversted on 05/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#include <vector>
#include <random>
#include "IBandit.h"

class FPL : public IBandit {
public:
    FPL(double eta, int K);
    int draw() override;
    void give_reward(int choice, double reward) override;
    void export_weights(std::string path) override;
private:
    void perturb_weights();
    std::vector<double> weights_;
    int K_;
    double eta_;
    std::exponential_distribution<double>  d_;
    std::mt19937 gen_;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
