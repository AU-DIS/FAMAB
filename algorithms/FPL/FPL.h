//
// Created by Mathias Tversted on 05/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#include <vector>
#include <random>
#include "FPLVectorWeightStrategy.h"
#include "NaiveRandomGenStrategy.h"
#include "../../utilities/random_gen.h"

class FPL
{
private:
    std::vector<double> _weights;
    std::mt19937 _gen;
    int _k;
    std::exponential_distribution<double> _exponential_distribution;

public:
    FPL(int k, double eta)
    {
        _weights = std::vector<double>(k, 1);
        _gen = random_gen();
        _exponential_distribution = std::exponential_distribution<double>(eta);
        _k = k;
    }

    void give_reward(size_t choice, double feedback)
    {
    }
    std::vector<double> &get_weights()
    {
        return _weights;
    }

    int choose()
    {

        for (auto &v : _weights)
            v += _exponential_distribution(_gen);
        /*
         * Draw is simply an arg-max, but std::vector does not support argmax
         * All code examples use chaining of algorithms that will only add useless computations,
         * so we implement it manually
         */
        int max_index = 0;
        double max_element = 0;

        for (int i = 0; i < _k; i++)
        {
            if (_weights[i] > max_element)
            {
                max_index = i;
                max_element = _weights[i];
            }
        }
        return max_index;
    }
    std::vector<int> choose(int K)
    {
        return std::vector<int>(_k, 1);
    }
    void give_reward(int choice, double feedback)
    {
        _weights[choice] += feedback;
    }

    void give_reward(std::vector<int> &indices, std::vector<double> &rewards)
    {
    }
};
#endif // EFFICIENT_MULTI_ARMED_BANDITS_FPL_H