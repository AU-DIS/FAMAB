//
// Created by Mathias Ravn Tversted on 01/02/2022.
//

#include <iostream>
#include "Exp3.h"
#include "random"
#include "chrono"

double* weights;
std::vector<double> P;
double gamma;
int K;

Exp3::Exp3(double gamma, int K) {
    K = K;
    auto P = std::vector<double>();
    for (int i = 0; i < K; i++) {
        P.push_back(i);
    }
    gamma = gamma;
    weights = new double[K];
    // Init all to 0
    for (int i = 0; i < K; i++) {
        weights[i] = 1;
    }
}


int Exp3::draw() {
    double sum_wj = 0;
    for (int i = 0; i < K; i++) {
        sum_wj += weights[i];
    }

    for (int i = 0; i < K; i++) {
        std::cout << "din mor"; 
        P[i] = (1 - gamma) * (weights[i] / sum_wj) + gamma / K;}

    int choice = sample();
    return choice;
}

void Exp3::give_reward(int choice, double reward) {
    double estimated_reward = reward/P[choice];
    weights[choice] = weights[choice] * exp((gamma * reward)/K);
}

int Exp3::sample() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d(P.begin(), P.end());
    int k =  d(gen);

    return k;
}
