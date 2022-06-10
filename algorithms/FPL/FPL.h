//
// Created by Mathias Tversted on 05/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPL_H
#include <vector>
#include <random>
#include "../../utilities/random_gen.h"
#include "../../utilities/argsort.h"
#include "iostream"

class FPL
{
private:
    std::vector<double> _weights;
    std::mt19937 _gen;
    int _k;
    std::exponential_distribution<double> _exponential_distribution;
    int current_round;
    double _eta;

public:
    FPL() = default;
    FPL(int k, double eta)
    {
        _weights = std::vector<double>(k, 1);
        _gen = random_gen();
        _exponential_distribution = std::exponential_distribution<double>(eta);
        _k = k;
        current_round = 0;
        _eta = eta;
    }
    FPL(FPL &b)
    {
        _weights = std::vector<double>(b._k, 1);
        _gen = random_gen();
        _exponential_distribution = std::exponential_distribution<double>(b._eta);
        _k = b._k;
        current_round = 0;
        _eta = b._eta;
    }

    void set_parameter(double eta)
    {
        _eta = eta;
        _exponential_distribution = std::exponential_distribution<double>(eta);
    }

    void give_reward(size_t choice, double feedback)
    {
        _weights[choice] += feedback;
    }
    std::vector<double> *get_weights()
    {
        return &_weights;
    }

    int choose()
    {

        current_round++;
        if (current_round % (int)_eta == 0)
        {
            double sum = 0;
            for (auto v : _weights)
                sum += v;
            for (auto &v : _weights)
                v /= sum;
        }

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
    std::vector<int> choose(int m)
    {
        current_round++;
        if (current_round % (int)_eta == 0)
        {
            double sum = 0;
            for (auto v : _weights)
                sum += v;
            for (auto &v : _weights)
                v /= sum;
        }

        for (auto &v : _weights)
            v += _exponential_distribution(_gen);

        auto w = argsort(_weights);
        auto r = std::vector<int>(m, 0);
        for (int i = 0; i < m; i++)
        {
            r[i] = w[_k - 1 - i];
        }
        return r;
    }
    void give_reward(int choice, double feedback)
    {
        _weights[choice] += feedback;
    }

    void give_reward(std::vector<int> &indices, std::vector<double> &rewards)
    {
        for (int i = 0; i < indices.size(); i++)
        {
            _weights[indices[i]] += rewards[i];
        }
    }
};
#endif // EFFICIENT_MULTI_ARMED_BANDITS_FPL_H