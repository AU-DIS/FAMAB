//
// Created by Kristoffer Strube on 31/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DATASET_THEORETICAL_BOUNDS_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DATASET_THEORETICAL_BOUNDS_H
#include "vector"
#include "../utilities/random_gen.h"
#include "random"
#include "iostream"

class dataset_theoretical_bounds{
private:
    std::vector<std::vector<double>> data_matrix;
    std::vector<int> iterators;
    double expected_reward;
    int _k;

public:
    dataset_theoretical_bounds(int rounds, int k) : _k(k) {
        auto gen = random_gen();
        std::discrete_distribution<int> d;

        for (int i = 0; i < k; i++) {
            iterators.push_back(0);
            std::vector<double> column;
            // In each arm we have some mean value for the bernoulli trial seperated across the interval [0,1]
            auto prob = 1.0 / ((double)k + 2.0) * ((double)i + 1.0);
            d = std::discrete_distribution<int>({1.0 - prob, prob});
            for (int j = 0; j < rounds; j++) {
                auto w = d(gen);
                column.push_back(w);
            }
            data_matrix.push_back(column);
        }

        expected_reward = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < rounds; j++) {
                expected_reward += data_matrix[i][j] / (double)k / (double)rounds;
            }
        }

        reset();
    }
    void reset() {
        iterators = std::vector<int>(data_matrix.size(), 0);
    }

    double expected_value() {
        return expected_reward;
    }

    auto feedback(int choice) {
        struct return_values {
            double feedback, regret;
        };
        auto index = iterators[choice];
        auto reward = data_matrix[choice][index];
        double max_reward = 0;
        for (int i = 0; i < _k; i++) {
            if (data_matrix[i][index] > max_reward) {
                max_reward = data_matrix[i][index];
            }
        }

        iterators[choice] += 1;

        return return_values{reward, max_reward - reward};
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATASET_THEORETICAL_BOUNDS_H
