//
// Created by Kristoffer Strube on 08-02-2022.
//


#include <vector>
#include <random>
#include "IWeightStrategy.h"
#include "VectorWeightStrategy.h"


VectorWeightStrategy::VectorWeightStrategy(int k, double gamma) {
        this->k = k;
        this->gamma = gamma;

        _probabilities = std::vector<double>();
        for (int i = 0; i < k; i++) {
            _probabilities.push_back(0);
        }
        _weights = std::vector<double>();
        // Init all to 0
        for (int i = 0; i < k; i++) {
            _weights.push_back(1);
        }
    };

int VectorWeightStrategy::sample() {
    std::discrete_distribution<> d(_probabilities.begin(), _probabilities.end());
    int k =  d(_random_gen);

    return k;
}
    int VectorWeightStrategy::choose()  {
        int k = this->k;
        double sum_wj = 0;
        for (int i = 0; i < k; i++) {
            sum_wj += _weights[i];
        }

        for (int i = 0; i < k; i++) {
            _probabilities[i] = (1 - gamma) * (_weights[i] / sum_wj) + gamma / k;
        }

        int choice = sample();
        return choice;
    }
    void VectorWeightStrategy::update_weight(int index, double weight)  {
        _weights[index] = weight;
    }
    std::vector<double> VectorWeightStrategy::get_weights()  {
        return _weights;
    }


