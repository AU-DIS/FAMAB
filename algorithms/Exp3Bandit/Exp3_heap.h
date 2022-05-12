//
// Created by Mathias Ravn Tversted on 31/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3_HEAP_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3_HEAP_H
#include "../../datastructures/Incremental_sum_heap.h"

class Exp3_heap
{

public:
    Incremental_sum_heap _distribution;

    Exp3_heap(int k, double gamma)
    {
        _k = k;
        _gamma = gamma;
        _weights = std::vector<double>(k, 1.0 / k);
        _distribution = Incremental_sum_heap(_weights);
        _additive_term = _gamma / _k;

        std::vector<double> power_weights(k, exp(_gamma / _k * ((1.0 / k)) - (1.0 / k)));
        _power_weights = Incremental_sum_heap(power_weights);

        max_weight = 1.0 / k;
    }

    int choose()
    {
        return _distribution.heap_sample();
    }
    std::vector<double> *get_weights()
    {
        return &_weights;
    }

    void give_reward(int index, double feedback)
    {
        double probability = (1 - _gamma) * exp(_gamma / _k * (_weights[index] - max_weight) - log(_power_weights.max_element())) + _gamma / _k;

        double est_reward = feedback / probability;
        _weights[index] += est_reward;

        _distribution.update(index, probability);
        _power_weights.update(index, exp(_gamma / _k * (_weights[index] - max_weight)));
        if (_weights[index] > max_weight)
            max_weight = _weights[index];
    }

private:
    int _k;
    double _gamma;
    double max_weight;
    std::vector<double> _weights;
    double _additive_term;
    Incremental_sum_heap _power_weights;
};

#endif // EFFICIENT_MULTI_ARMED_BANDITS_EXP3_HEAP_H
