//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H

#include <vector>
#include "cmath"
#include "algorithm"
#include "iostream"
#include "../../utilities/argsort.h"
#include "DepRoundALIASStrategy.h"

#include "cmath"

class Exp3m {
private:
    int _k;
    int _m;
    DepRoundALIASStrategy _sampling;
    double get_alpha(double rhs, std::vector<size_t> &argsorted) {
        double weight_sum = 0;
        for (auto v : _weights) weight_sum += v;
        for (size_t i = 0; i < _k; i++) {
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

    Exp3m(int m, int k, double gamma) : _m(m), _k(k), _gamma(gamma) {
        _sampling = DepRoundALIASStrategy();
        for (int i = 0; i < _k; i++) {
            _weights.push_back(1.0/_k);
        }
    };
    std::vector<int> choose(int m) {
        auto sorted_weight_indices = argsort(_weights);

        double sum_weights = 0;
        for (double v: _weights) sum_weights += v;

        double threshold = (1.0/_m-_gamma/_k)*sum_weights/(1-_gamma);
        std::vector<double> weights_prime;
        //std::cout << "back" << sorted_weight_indices.back() << std::endl;
        //std::cout << "front" << sorted_weight_indices.front() << std::endl;
        if (_weights[sorted_weight_indices.back()] >= threshold) {
            double rhs =  (1.0/_m-_gamma/_k)/(1-_gamma);
            double alpha_t = get_alpha(rhs, sorted_weight_indices);
            for (size_t i = 0; i < _k; i++) {
                weights_prime.push_back(std::min(alpha_t, _weights[i]));
            }
        }
        else {
            for (size_t i = 0; i < _k; i++) {
                weights_prime.push_back(_weights[i]);
            }
        }
        double w_sum = 0;
        for (auto v: weights_prime) w_sum += v;
        std::vector<double> probabilities;
        probabilities.reserve(_k);

        for (int i = 0; i < _k; i++) {
            double p = _m * ( (1-_gamma)*weights_prime[i]/w_sum + _gamma/_k);
            probabilities.push_back(p);
        }
        _last_probabilities = probabilities;
        return _sampling.dependent_weighted_choices(probabilities, _m);
    };
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards) {
        for (int i = 0; i < indices.size(); i++) {
            int k = indices[i];
            double r = rewards[k];
            _weights[k] *= exp(_m*_gamma*(r/_last_probabilities[k])/_k);
        }
        double sum_weights = 0;
        for (double v: _weights) sum_weights += v;
        for (int j = 0; j < _weights.size(); j++) {
            _weights[j] = _weights[j]/sum_weights;
        }

    };
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_H
