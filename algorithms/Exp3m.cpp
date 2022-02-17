//
// Created by Mathias Ravn Tversted on 11/02/2022.
//

#include "Exp3m.h"
#include "algorithm"
#include "../utilities/argsort.cpp"
#include "iostream"
#include "random"


Exp3m::Exp3m(int K, int k, double gamma) {
    _K = K;
    _k = k;
    _gamma = gamma;
    for (int i = 0; i < _K; i++) {
        _weights.push_back(1.0);
    }
}

std::vector<int> Exp3m::choose() {
    auto sorted_weight_indices = argsort(_weights);

    double sum_weights = 0;
    for (double v: _weights) sum_weights += v;

    double threshold =  (1.0/_k-_gamma/_K)*sum_weights/(1-_gamma);
    std::vector<double> weights_prime;

    //std::cout << _weights[sorted_weight_indices.back()] << " >= " << threshold << std::endl;
    if (_weights[sorted_weight_indices.back()] >= threshold) {
      //  std::cout << "din mor" << std::endl;
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
    return depround(probabilities);
}

void Exp3m::give_reward(std::vector<int> &indices, std::vector<double> &rewards) {
    for (int i = 0; i < indices.size(); i++) {
        int k = indices[i];
        double r = rewards[i];
        _weights[k] *= exp(_k*_gamma*(r/_last_probabilities[k])/_K);
    }
}

std::vector<int> Exp3m::depround(std::vector<double> probabilities) {
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> uniform(0, 1);

    std::vector<int> candidates;
    candidates.reserve(_K);
    for (int i = 0; i < _K; i++) candidates.push_back(i);

    std::vector<int> return_indices;
    return_indices.reserve(_k);

    while (candidates.size() > 1) {
        int i = candidates.back();
        candidates.pop_back();
        int j = candidates.back();
        candidates.pop_back();

        double alpha = 1 - probabilities[i] < probabilities[j] ? 1 - probabilities[i] : probabilities[j];
        double beta = probabilities[i] < 1 - probabilities[j] ? probabilities[i] : 1 - probabilities[j];

        double r = uniform(rng);

        if (r > beta / (alpha + beta)) {
            probabilities[i] += alpha;
            probabilities[j] -= alpha;
        } else {
            probabilities[i] -= beta;
            probabilities[j] += beta;
        }

        if (probabilities[i] >= 0.99999 && probabilities[i] <= 1) return_indices.push_back(i);
        else if (probabilities[i] > 0.0000000000) candidates.push_back(i);

        if (probabilities[j] >= 0.99999 && probabilities[j] <= 1) return_indices.push_back(j);
        else if (probabilities[j] > 0.0000000000) candidates.push_back(j);

    }

    return return_indices;
}

double Exp3m::get_alpha(double rhs, std::vector<size_t> &argsorted) {
    double weight_sum = 0;
    for (auto v : _weights) weight_sum += v;
    //std::cout << rhs << std::endl;
    for (size_t i = 0; i < _K; i++) {
        double alpha_candidate = (rhs * weight_sum) / (1 - i * rhs);
        double current_value = _weights[argsorted[i]];
        if (alpha_candidate > current_value) {
            //std::cout << alpha_candidate << std::endl;
            return alpha_candidate;}
        weight_sum -= current_value;
    }
    abort();
}



