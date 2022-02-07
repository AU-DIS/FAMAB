//
// Created by Mathias Ravn Tversted on 01/02/2022.
//

#include <iostream>
#include "Exp3.h"
#include "random"
#include "chrono"
#include "utilities/weight_exporter.cpp"


Exp3::Exp3(double gamma, int K) {
    K_ = K;
    auto P = std::vector<double>();
    P_ = P;
    for (int i = 0; i < K; i++) {
        P_.push_back(i);
    }
    gamma_ = gamma;
    weights_ = std::vector<double>();
    // Init all to 0
    for (int i = 0; i < K_; i++) {
        weights_.push_back(1);
    }
}

int Exp3::draw() {
    double sum_wj = 0;
    for (int i = 0; i < K_; i++) {
        sum_wj += weights_[i];
    }

    for (int i = 0; i < K_; i++) {
        P_[i] = (1 - gamma_) * (weights_[i] / sum_wj) + gamma_ / K_;}

    int choice = sample();
    return choice;
}

void Exp3::give_reward(int choice, double reward) {
    double estimated_reward = reward/P_[choice];
    weights_[choice] = weights_[choice] * exp((gamma_ * estimated_reward)/K_);
}

int Exp3::sample() {
    std::discrete_distribution<> d(P_.begin(), P_.end());
    int k =  d(gen_);

    return k;
}

void Exp3::export_weights(std::string path) {
    write_weights(weights_, path);
}
