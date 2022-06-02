//
// Created by kaspe on 04-05-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_HEAP_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_HEAP_H
#include <vector>
#include "cmath"
#include "algorithm"
#include "iostream"
#include "../../utilities/argsort.h"
#include "../../datastructures/Incremental_sum_heap.h"

#include "cmath"
class Exp3m_heap
{
private:
    int _k;
    int _m;
    double max_weight;
    std::vector<double> _weights;
    double _additive_term;
    Incremental_sum_heap _power_weights;

public:
    double _gamma;
    std::vector<double> _last_probabilities;
    Incremental_sum_heap _distribution;

    Exp3m_heap(int m, int k, double gamma) : _m(m), _k(k), _gamma(gamma)
    {
        _weights = std::vector<double>(k, 1.0 / k);
        _distribution = Incremental_sum_heap(_weights);
        //std::vector<double> power_weights(k, exp(_gamma / _k * ((1.0 / k)) - (1.0 / k)));
        //_power_weights = Incremental_sum_heap(power_weights);

        //max_weight = 1.0 / k;
    };
    std::vector<int> choose(int m)
    {

        /*double w_sum = 0;
        for (auto v : _weights)
            w_sum += v;*/
        std::vector<double> probabilities;
        probabilities.reserve(_k);

        for (int i = 0; i < _k; i++)
        {
            double p = _m * ((1 - _gamma) * _weights[i] / _distribution.max_element() + _gamma / _k);
            probabilities.push_back(p);
        }
        _last_probabilities = probabilities;
        return _distribution.heap_sample(m);
    };
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards)
    {
        for (int i = 0; i < indices.size(); i++)
        {
            int k = indices[i];
            double r = rewards[k];
            _weights[k] *= exp(_m * _gamma * (r / _last_probabilities[k]) / _k);
        }
        /*double sum_weights = 0;
        for (double v : _weights)
            sum_weights += v;*/
        for (int j = 0; j < _weights.size(); j++)
        {
            _weights[j] = _weights[j] / _distribution.max_element();
            _distribution.update(j, _weights[j]);
        }
    };
};

#endif // EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_HEAP_H
