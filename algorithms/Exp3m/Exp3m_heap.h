//
// Created by kasper on 04-05-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_HEAP_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_HEAP_H
#include <vector>
#include "cmath"
#include "algorithm"
#include "iostream"
#include "../../utilities/argsort.h"
#include "../../datastructures/Incremental_sum_heap.h"
#include "../../datastructures/Incremental_product_heap.h"

#include "cmath"
class Exp3m_heap
{
private:
    int _k;
    int _m;
    double max_weight;
    double weight_sum;

    double _additive_term;
    Incremental_sum_heap _power_weights;

public:
    std::vector<double> _weights;
    double _gamma;
    std::vector<double> _last_probabilities;
    Incremental_sum_heap _distribution;

    std::vector<double>* get_weights() {
        return &_weights;
    }


    Exp3m_heap() = default;

    Exp3m_heap(int m, int k, double gamma) : _m(m), _k(k), _gamma(gamma)
    {
        _weights = std::vector<double>(k, 1.0/k);
        _distribution = Incremental_sum_heap(_weights);
        _last_probabilities.reserve(_k);
        std::vector<double> power_weights(k, exp(_gamma / _k * ((1.0 / k)) - (1.0 / k)));
        _power_weights = Incremental_sum_heap(power_weights);

        max_weight = 1.0/k;
        weight_sum = k;    };
    std::vector<int> choose(int m)
    {

        //std::vector<double> probabilities;
        //probabilities.reserve(_k);

        /*double sum_reduced_power_weights = 0;
        double mw = *max_element(_weights.begin(), _weights.end());
        for (int i = 0; i < _k; i++)
        {
            sum_reduced_power_weights += exp((_weights[i] - mw));
        }*/
        std::vector<int> choices = _distribution.heap_sample(m);

        for (int i : choices) {
        //for (int i = 0; i < _k; i++) {
            double p = _m * ( (1 - _gamma) * exp(_weights[i] - max_weight - log(weight_sum) ) + _gamma/ _k);
            _last_probabilities[i] = p;
        }

        //_last_probabilities = probabilities;
        return choices; //Incremental_sum_heap(probabilities).heap_sample(m); //_distribution.heap_sample(m);
    };
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards)
    {
        for (int i : indices) {
            double old = _weights[i];
            _weights[i] += _m*_gamma*(rewards[i]/_last_probabilities[i])/_k; //implicit log
            //weight_sum += _m*_gamma*(rewards[i]/_last_probabilities[i])/_k;
            _distribution.update(i, _last_probabilities[i]);
            //_power_weights.update(i, exp(_weights[i] ));
            if (_weights[i] > max_weight) {
                //Remove old
                weight_sum -= exp(old - max_weight);
                //Correct other weigths
                weight_sum *= exp(max_weight - _weights[i]);
                //Add new replacement
                weight_sum += 1;
                max_weight = _weights[i];
            } else {
                //Remove old
                weight_sum -= exp(old - max_weight);
                //Add replacement
                weight_sum += exp( _weights[i] - max_weight);
            }
        }
        /*double sum_weights = 0;
        for (double v : _weights)
            sum_weights += v;*/
        /*for (int j = 0; j < _weights.size(); j++)
        {
            _weights[j] = _weights[j] / _distribution.max_element();
            _distribution.update(j, _weights[j]);
        }*/
    };
};

#endif // EFFICIENT_MULTI_ARMED_BANDITS_EXP3M_HEAP_H
