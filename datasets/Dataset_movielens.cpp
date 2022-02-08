//
// Created by Mathias Ravn Tversted on 08/02/2022.
//

#include <string>
#include "Dataset_movielens.h"
#include "dataloaders.cpp"


Dataset_movielens::Dataset_movielens(const std::string& path) {
    _data_matrix = load_choice_reward_dataset(path);
    k = _data_matrix.size();
    reward_min = 0;
    reward_max = 5;
    _iterators = new int [k];
    for (int i = 0; i < k; i++) {
        _iterators[i] = 0;
    }
}

double Dataset_movielens::feedback(int choice) {
    double r = _data_matrix[choice][_iterators[choice]];
    _iterators[choice] = (_iterators[choice] + 1) % _data_matrix[choice].size();
    return r/reward_max;
}

// Not sure if this is stricly needed, but not taking any chances
Dataset_movielens::~Dataset_movielens() {
    free(_iterators);
}
