//
// Created by Mathias Ravn Tversted on 08/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DATASET_MOVIELENS_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DATASET_MOVIELENS_H


#include <vector>

/// The Movielens dataset contains 20000263 reviews across 27278 movies.
/// The dataset must be downloaded at https://www.kaggle.com/grouplens/movielens-20m-dataset?select=rating.csv
/// Remember to process it using data_processors/movielens_preprocessor.py
///
class Dataset_movielens {
public:
    explicit Dataset_movielens(const std::string& path);
    double feedback(int choice);
    int k = 0;
    int reward_max = 0;
    int reward_min = 0;
    virtual ~Dataset_movielens();


private:
    std::vector<std::vector<double>> _data_matrix;
    int* _iterators;


};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATASET_MOVIELENS_H
