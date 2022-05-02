//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H

#include <vector>
#include "algorithm"
#include "iostream"
#include "../../utilities/argsort.h"

#include "cmath"
template<typename ALIASStrategy>
class Exp3m {
private:
    int _k;
    int _K;
    ALIASStrategy &_ALIASStrategy;
    double get_alpha(double rhs, std::vector<size_t> &argsorted) {
        double weight_sum = 0;
        for (auto v : _weights) weight_sum += v;
        for (size_t i = 0; i < _K; i++) {
            double alpha_candidate = (rhs * weight_sum) / (1 - i * rhs);
            double current_value = _weights[argsorted[i]];
            if (alpha_candidate > current_value) {
                return alpha_candidate;}
            weight_sum -= current_value;
        }
        abort();
    };
public:
    double _gamma;
    std::vector<double> _last_probabilities;
    std::vector<double> _weights;

    Exp3m(int K, int k, double gamma, ALIASStrategy &as) : _K(K), _k(k), _gamma(gamma), _ALIASStrategy(as) {
        for (int i = 0; i < _K; i++) {
            _weights.push_back(1.0);
        }
    };
    std::vector<int> choose(int k) {
        auto sorted_weight_indices = argsort(_weights);

        double sum_weights = 0;
        for (double v: _weights) sum_weights += v;

        double threshold =  (1.0/_k-_gamma/_K)*sum_weights/(1-_gamma);
        std::vector<double> weights_prime;

        if (_weights[sorted_weight_indices.back()] >= threshold) {
            double rhs =  (1.0/_k-_gamma/_K)/(1-_gamma);
            double alpha_t = get_alpha(rhs, sorted_weight_indices);
            for (size_t i = 0; i < _K; i++) {
                weights_prime.push_back(std::min(alpha_t, _weights[i]));
            }
        }
        else {
            for (size_t i = 0; i < _K; i++) {
                weights_prime.push_back(_weights[i]);
            }
        }

        double w_sum = 0;
        for (auto v: weights_prime) w_sum += v;
        std::vector<double> probabilities;
        probabilities.reserve(_K);

        for (int i = 0; i < _K; i++) {
            double p = _k * ( (1-_gamma)*weights_prime[i]/w_sum + _gamma/_K);
            probabilities.push_back(p);
        }
        _last_probabilities = probabilities;
        return _ALIASStrategy.dependent_weighted_choices(probabilities, _k);
    };
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards) {
        for (int i = 0; i < indices.size(); i++) {
            int k = indices[i];
            double r = rewards[i];
            _weights[k] *= exp(_k*_gamma*(r/_last_probabilities[k])/_K);
        }
    };
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H
