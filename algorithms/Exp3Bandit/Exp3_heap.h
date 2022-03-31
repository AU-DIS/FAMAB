//
// Created by Mathias Ravn Tversted on 31/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3_HEAP_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3_HEAP_H
#include "../../datastructures/Incremental_sum_heap.h"


class Exp3_heap {

public:
    Incremental_sum_heap _distribution;

    Exp3_heap(int k, double gamma) {
        _k = k;
        _gamma = gamma;
        _weights = std::vector<double>(k, 1.0/k);
        _distribution = Incremental_sum_heap(_weights);
        _additive_term = _gamma/_k;

    }

    int choose() {
        return _distribution.heap_sample();
    }

    void give_reward(int index, double feedback) {
        double probability = (1 - _gamma)/(_distribution.max_element()) * _weights[index] + _additive_term;

        double est_reward = feedback / probability;
        _weights[index] *= exp((_gamma * est_reward)/_k);

        _distribution.update(index, _weights[index]);

    }

private:
    int _k;
    double _gamma;
    std::vector<double> _weights;
    double _additive_term;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3_HEAP_H
