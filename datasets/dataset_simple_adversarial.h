//
// Created by Mathias Ravn Tversted on 03/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DATASET_SIMPLE_ADVERSARIAL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DATASET_SIMPLE_ADVERSARIAL_H

#include "vector"
#include "../utilities/random_gen.h"
#include "random"
#include "iostream"
class dataset_simple_adversarial {
private:
    std::vector<std::vector<double>> data_matrix;
    std::vector<int> iterators;
public:
    dataset_simple_adversarial(int K, int number_of_rounds, double p) {
        auto gen = random_gen();

        auto p1 = p;
        auto weights_before = {p1, 1 - p1};
        auto p2 = 0.1;
        auto weights_after = {p2, 1 - p2};

        std::discrete_distribution<int> d1(weights_before.begin(), weights_before.end());
        std::discrete_distribution<int> d2(weights_after.begin(), weights_after.end());

        for (int i = 0; i < K; i++) {
            iterators.push_back(0);
            std::vector<double> column;
            for (int j = 0; j < number_of_rounds; j++) {
                double w = (double)j >= ((double)number_of_rounds)/2 ? d1(gen) : d2(gen);
                column.push_back(w);
            }
            data_matrix.push_back(column);
        }
        reset();
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

#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATASET_SIMPLE_ADVERSARIAL_H
