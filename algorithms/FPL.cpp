//
// Created by Mathias Tversted on 05/02/2022.
//

#include <vector>
#include <random>
#include "FPL.h"

FPL::FPL(double eta, int K) {
    K_ = K;
    eta_ = eta;
    // Init all weights to 0
    for (int i = 0; i < K_; i++) {
        weights_.push_back(0);
    }
    std::exponential_distribution<double>  d(eta_);
    d_ = d;

}

void FPL::perturb_weights() {
    for (int i = 0; i < K_; i++) {
        weights_[i] += d_(gen_);
    }
}

int FPL::draw() {
    perturb_weights();
    /*
    * Draw is simply an arg-max, but std::vector does not support argmax
    * All code examples use chaining of algorithms that will only add useless computations,
    * so we implement it manually
     */
    int max_index = 0;
    double max_element = 0;

    for (int i = 0; i < K_; i++) {
        if (weights_[i] > max_element) {
            max_index = i;
            max_element = weights_[i];
        }
    }
    return max_index;
}

void FPL::give_reward(int choice, double reward) {
    weights_[choice] += reward;
}
