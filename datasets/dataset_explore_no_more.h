//
// Created by Mathias Ravn Tversted on 01/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DATASET_EXPLORE_NO_MORE_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DATASET_EXPLORE_NO_MORE_H
#include "vector"
#include "../utilities/random_gen.h"
#include "random"
#include "iostream"

class dataset_explore_no_more{
private:
    std::vector<std::vector<double>> data_matrix;
    std::vector<int> iterators;

public:
    dataset_explore_no_more() {
        auto number_of_rounds = 1000000;
        auto delta = 0.1;
        auto gen = random_gen();
        std::discrete_distribution<int> d;

        for (int i = 0; i < 8; i++) {
            iterators.push_back(0);
            std::vector<double> column;
            d = std::discrete_distribution<int>(0.5, 0.5);
            for (int j = 0; j < number_of_rounds; j++) {
                auto w = d(gen);
                column.push_back(w);
            }
            data_matrix.push_back(column);
        }
        std::vector<double> ninth_column;
        d = std::discrete_distribution<int>(0.5+delta, 0.5-delta);
        for (int j = 0; j < number_of_rounds; j++) {
            auto w = d(gen);
            ninth_column.push_back(w);
        }
        data_matrix.push_back(ninth_column);
        std::vector<double> tenth_column;
        d = std::discrete_distribution<int>(0.5+delta, 0.5-delta);
        for (int j = 0; j < number_of_rounds/2; j++) {
            auto w = d(gen);
            tenth_column.push_back(w);
        }
        d = std::discrete_distribution<int>(0.5+delta*4, 0.5-delta*4);
        for (int j = 0; j < number_of_rounds/2; j++) {
            auto w = d(gen);
            tenth_column.push_back(w);
        }
        data_matrix.push_back(tenth_column);
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

#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATASET_EXPLORE_NO_MORE_H
