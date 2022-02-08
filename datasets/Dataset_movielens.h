//
// Created by Mathias Ravn Tversted on 08/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DATASET_MOVIELENS_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DATASET_MOVIELENS_H


#include <vector>
#include "IDataset.h"

class Dataset_movielens : public IDataset {
public:
    explicit Dataset_movielens(const std::string& path);
    virtual double feedback(int choice) override;

    virtual ~Dataset_movielens();

private:
    std::vector<std::vector<double>> _data_matrix;
    int* _iterators;


};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATASET_MOVIELENS_H
