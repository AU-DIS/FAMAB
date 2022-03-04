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
    double expected_reward;
public:
    dataset_simple_adversarial(int K, int number_of_rounds) {
        for (int i = 0; i < K; i++) iterators.push_back(0);

        for (int i = 0; i < K; i++) {
            std::vector<double> row;
            for (int j = 0; j < number_of_rounds; j++) {
                row.push_back(0.0);
            }
            data_matrix.push_back(row);
        }

        for (int column = 0; column < K; column++) {
            for (int row = 0; row < number_of_rounds; row++) {
                double r = row >= (number_of_rounds/2) ? row % 2 : (row + 1) % 2;
                data_matrix[column][row] = r;
            }
        }

        std::vector<double> column_averages;
        for (int i = 0; i < K; i++) {
            column_averages.push_back(0.0);
            for (int j = 0; j < number_of_rounds; j++) {
                column_averages[i] += data_matrix[i][j];
            }
        }

        for (auto &r : column_averages)
        {
            r /= number_of_rounds;
        }

        for (auto avg : column_averages) expected_reward += avg;
        expected_reward /= K;

        reset();
    }
    void reset() {
        for (auto &i : iterators) i = 0;
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
        iterators[choice] += 1;
        return return_values{reward, 1 - reward};
    }

};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATASET_SIMPLE_ADVERSARIAL_H
