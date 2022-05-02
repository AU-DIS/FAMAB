//
// Created by Mathias Tversted on 02/05/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_TSALLIS_Heap_H
#define EFFICIENT_MULTI_ARMED_BANDITS_TSALLIS_Heap_H

#include "../../datastructures/Incremental_sum_heap.h"
#include "../../utilities/argsort.h"

class Tsallis_Heap
{
private:
    Incremental_sum_heap _distribution;
    int _k;
    int current_round;
    int update_interval;
    std::vector<double> _probabilities;
    std::vector<double> _number_chosen;

public:
    std::vector<double> _cumulative_losses;

    explicit Tsallis_Heap(int k)
    {
        _k = k;
        _cumulative_losses = std::vector<double>(k, 1);
        _number_chosen = std::vector<double>(k, 0);
        _probabilities = std::vector<double>(k, 1 / k);

        _distribution = Incremental_sum_heap(_cumulative_losses);
        update_interval = (int)k * log2(k);
        current_round = 1;
    }
    int choose()
    {
        current_round += 1;
        int c = _distribution.heap_sample();
        _number_chosen[c] += 1;
        return c;
    }

    void give_reward(size_t index, double feedback)
    {
        _cumulative_losses[index] += feedback == 1 ? 0.1 : -0.3;
        _distribution.update(index, _cumulative_losses[index]);
    }
};

#endif // EFFICIENT_MULTI_ARMED_BANDITS_TSALLIS_Heap_H
