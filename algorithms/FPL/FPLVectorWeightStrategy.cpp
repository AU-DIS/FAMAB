//
// Created by Kristoffer Strube on 14-02-2022.
//

#include "FPLVectorWeightStrategy.h"
#include "iostream"

FPLVectorWeightStrategy::FPLVectorWeightStrategy(size_t k) : _k(k) {
    // Init all weights to 0
    for (int i = 0; i < k; i++) {
        _weights.push_back(0);
    }
}

void FPLVectorWeightStrategy::add_to_weight(size_t i, double weight) {
    _weights[i] += weight;
}

void FPLVectorWeightStrategy::add_to_weights(std::vector<double> vector) {
    for (int i = 0; i < vector.size(); i++) {
        _weights[i] = _weights[i] + vector[i];
    }
}

int FPLVectorWeightStrategy::max_weight() {
    /*
    * Draw is simply an arg-max, but std::vector does not support argmax
    * All code examples use chaining of algorithms that will only add useless computations,
    * so we implement it manually
     */
    int max_index = 0;
    double max_element = 0;

    for (int i = 0; i < _k; i++) {
        if (_weights[i] > max_element) {
            max_index = i;
            max_element = _weights[i];
        }
    }
    return max_index;
}
std::vector<double> FPLVectorWeightStrategy::get_weights() {
    return _weights;
}