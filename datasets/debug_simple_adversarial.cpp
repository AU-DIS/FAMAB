//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#include "debug_simple_adversarial.h"
#include "random"
#include "vector"


debug_simple_adversarial::debug_simple_adversarial(int K, int rounds) {
    k = K;
    _rounds = rounds;
    // Modify as needed
    constexpr int MIN = 0;
    constexpr int MAX = 1;
    std::srand(69420);
    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::normal_distribution<double> d{10,40};
    _gen = gen;
    _d = d;

    _data_matrix.reserve(k);
}

void debug_simple_adversarial::randomize_weights() {
    double min_element = 1000000;
    double max_element = 0;
    for (int i = 0; i < k; i++) {
        double v = _d(_gen);
        _data_matrix.push_back(v);
        if (v < min_element) min_element = v;
        if (v > max_element) max_element = v;
    }
    // Range normalize all values
    for (int i = 0; i < k; i++) {
        _data_matrix[i] = (_data_matrix[i] - min_element)/(max_element - min_element);
    }
}

double debug_simple_adversarial::feedback(int choice) {
    if ((_current_round % (_rounds/10) == 0)) {
        randomize_weights();
    }
    _current_round += 1;
    return _data_matrix[choice];
}


