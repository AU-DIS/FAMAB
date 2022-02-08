//
// Created by Kristoffer Strube on 08-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_CPP
#define EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_CPP

#include <vector>
#include <random>
#include "IWeightStrategy.cpp"


class VectorWeightStrategy : public IWeightStrategy {
private:
    int sample() {
        std::discrete_distribution<> d(_probabilities.begin(), _probabilities.end());
        int k =  d(_random_gen);

        return k;
    }
    std::vector<double> _weights;
    std::vector<double> _probabilities;
    std::mt19937 _random_gen;
public:
    VectorWeightStrategy(int k, double gamma) {
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
    int choose() override {
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
    void update_weight(int index, double weight) override {
        _weights[index] = weight;
    }
    std::vector<double> get_weights() override {
        return _weights;
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_CPP
