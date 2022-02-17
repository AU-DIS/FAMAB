//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#include "debug_simple_stochastic.h"
#include "random"

/// This debug data set is stochastic and contains distributes a single reward across
/// all the choices. Each choice is given a single static reward from a gaussian distribution
/// with mean 10 and stddev 40. The values are range normalized to [0, 1].
debug_simple_stochastic::debug_simple_stochastic(int K, int number_to_sample) {
    k = K;

    // Modify as needed
    constexpr int MIN = 0;
    constexpr int MAX = 1;
    std::srand(69420);
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<double> d{10,40};

    _data_matrix.reserve(k);
    double min_element = 1000000;
    double max_element = 0;
    for (int i = 0; i < k; i++) {
        double v = d(gen);
        _data_matrix.push_back(v);
        if (v < min_element) min_element = v;
        if (v > max_element) max_element = v;
    }
    // Range normalize all values
    for (int i = 0; i < k; i++) {
        _data_matrix[i] = (_data_matrix[i] - min_element)/(max_element - min_element);
    }
    auto sorted = std::vector<double>(_data_matrix);
    std::sort(sorted.begin(), sorted.end());

    max_possible_reward = *std::max_element(_data_matrix.begin(), _data_matrix.end());
    //reward_min = *std::min_element(_data_matrix.begin(), _data_matrix.end());

    for (int i = 0; i < number_to_sample; i++) {
        reward_min += _data_matrix[i];
        reward_max += _data_matrix[K - 1 - i];
    }
    max_regret = reward_max - reward_min;
    min_regret = 0;
}

double debug_simple_stochastic::feedback(int choice, double &regret) {
    regret = max_possible_reward - _data_matrix[choice];
    return _data_matrix[choice];
}