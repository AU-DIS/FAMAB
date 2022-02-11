//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#include "DExp3.h"
#include<tuple>
#include <vector>
#include "iostream"


DExp3::DExp3(int K, double gamma, double eta) {
    _weights.reserve(K);
    _k = K;
    _gamma = gamma;
    _eta = eta;

    for (int i = 0; i < _k; i++) {
        _weights.push_back(1.0/_k);
    }
}

std::tuple<double, double> DExp3::choose() {
    std::discrete_distribution<double> d(_weights.begin(), _weights.end());
    return std::make_tuple(d(_random_gen), d(_random_gen));
}

void DExp3::give_reward(int x, int y, int winner, int round) {

    std::vector<double> s_tilde;
    s_tilde.reserve(_k);

    for (int i = 0; i < _k; i++) {
        double j_sum = 0;
        for (int j = 0; j < _k; j++) {
            j_sum += ((y == j ? 1 : 0) * winner)/_weights[j];
        }
        s_tilde.push_back((x == i ? 1 : 0)/(_k * _weights[i]) * j_sum);
    }
    s_tilde_t.push_back(s_tilde);
    for (int i = 0; i < _k; i++) {
        double top = 0;
        double bottom = 0;
        for (int t = 0; t < round; t++) {
            top += s_tilde_t[t][i];
        }
        for (int j = 0; j < _k; j++) {
            double bottom_inner = 0;
            for (int t = 0; t < round; t++){
                bottom_inner += s_tilde_t[t][j];
            }
            bottom_inner *= _eta;
            bottom_inner = exp(bottom_inner);
            bottom += bottom_inner;
        }
        top = exp(_eta * top);
        double q_tilde = top/bottom;
        _weights[i] = (1 - _gamma) * q_tilde + (_gamma/_k);
    }
}

