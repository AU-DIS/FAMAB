//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DEXP3_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DEXP3_H

#include "random"

class DExp3 {
public:
    DExp3(int K, double gamma, double eta);
    std::tuple<double, double> choose();
    void give_reward(int x, int y, int winner, int round);
    std::vector<double> _weights;
private:
    std::mt19937 _random_gen;
    int _k;

    std::vector<std::vector<double>> s_tilde_t;
    double _gamma;
    double _eta;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_DEXP3_H
