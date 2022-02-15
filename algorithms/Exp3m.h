//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H

#include <vector>

class Exp3m {
public:
    Exp3m(int K, int k, double gamma);
    int _k;
    int _K;
    double _gamma;
    std::vector<int> choose();
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards);
    std::vector<int> depround(std::vector<double> probabilities);
private:
    std::vector<double> _weights;
    std::vector<double> _last_probabilities;
    double get_alpha(double rhs, std::vector<size_t> &argsorted);

};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H
