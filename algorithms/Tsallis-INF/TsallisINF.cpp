//
// Created by Mathias Ravn Tversted on 22/02/2022.
//

#include <vector>
#include "TsallisINF.h"
#include "tgmath.h"
#include <random>
#include "iostream"

TsallisINF::TsallisINF(int K) {
    //double alpha = 0.5;
    cumulative_losses.reserve(K);
    for (int i = 0; i < K; i++) cumulative_losses.push_back(0);
}

double TsallisINF::compute_eta(int t) {
    return 1 / sqrt(std::max(1, t));
}

/// This assumes alpha = 1/2
std::vector<double> TsallisINF::newtons_method_weights(std::vector<double> &losses, double eta) {
    std::vector<double> weights;
    double x_previous = _x;
    double x_estimated = _x;
    for (int i = 0; i < losses.size(); i++) weights.push_back(0);

    do {
        x_previous = x_estimated;
        for (int i = 0; i < losses.size(); i++) weights[i] = 4 * pow((eta * (losses[i] - x_previous)), -2);
        double w_sum_powered = 0;
        double w_sum = 0;
        for (auto w: weights) {
            w_sum_powered += pow(w, (3 / 2));
            w_sum += w;
        }
        x_estimated = x_previous - (w_sum - 1) / (eta * w_sum_powered);
        //std::cout << std::min(x_previous, x_estimated)/std::max(x_previous, x_estimated) << std::endl;
    }
    while (std::min(x_previous, x_estimated)/std::max(x_previous, x_estimated) >= 1.1);
    _x = x_estimated;

    // It is assumed that weights are normalized. This is called "trusts".
    double w_sum = 0;
    for (auto w: weights) w_sum += w;
    for (auto &w : weights) w = w/w_sum;
    return weights;
}

int TsallisINF::choose() {
    // Keep x?
    _weights = newtons_method_weights(cumulative_losses, compute_eta(_t));
    std::mt19937 _random_gen(static_cast<long unsigned int>(time(0)));
    std::discrete_distribution<> d(_weights.begin(), _weights.end());
    int s =  d(_random_gen);
    _t += 1;
    return s;
}

void TsallisINF::give_reward(size_t index, double feedback) {
    // We can either use IW or RV to construct the estimated reward

    // This is RW, we should also try RV, which is a reduced variance estimator
    double estimated_reward = feedback/_weights[index];
    cumulative_losses[index] += estimated_reward;
}




