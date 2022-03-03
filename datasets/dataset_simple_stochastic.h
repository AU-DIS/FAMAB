//
// Created by Mathias Ravn Tversted on 01/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DATASET_SIMPLE_STOCHASTIC_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DATASET_SIMPLE_STOCHASTIC_H
#include "vector"
#include "../utilities/random_gen.h"
#include "random"
#include "iostream"

class dataset_simple_stochastic{
private:
    std::vector<std::vector<double>> data_matrix;
    std::vector<int> iterators;

public:
    /// @param values K, number_of_rounds, probability P
    ///
    ///
    dataset_simple_stochastic(int K, int number_of_rounds, double p) {
        auto gen = random_gen();
        auto weights = {p, 1 - p};
        std::discrete_distribution<int> d(weights.begin(), weights.end());

        for (int i = 0; i < K; i++) {
            iterators.push_back(0);
            std::vector<double> column;
            for (int j = 0; j < number_of_rounds; j++) {
                auto w = d(gen);
                column.push_back(w);
            }
            data_matrix.push_back(column);
        }
    }
    void reset() {
        for (auto &i : iterators) i = 0;
    }

    auto feedback(int choice) {
        struct return_values {
            double feedback, regret;
        };
        auto index = iterators[choice];
        auto reward = data_matrix[choice][index];
        iterators[choice] += 1;
        return return_values{reward, 1 - reward};
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATASET_SIMPLE_STOCHASTIC_H
