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
#include "../../datastructures/Incremental_LSE_sum_heap.h"
#include "../../datastructures/Incremental_sum_heap.h"
#include "../../datastructures/Incremental_product_heap.h"
//#include "../utilities/random_gen.h"

#include "cmath"
class Exp3m_heap
{
private:
    int _k;
    int _m;
    double max_weight;
    double weight_sum;
    int cnt = 0;
    double _additive_term;
    //Incremental_sum_heap _power_weights;
    std::uniform_real_distribution<double> _uni;
    std::mt19937 _random_gen = random_gen();

public:
    std::vector<double> _weights;
    double _gamma;
    std::vector<double> _last_probabilities;
    Incremental_LSE_sum_heap _distribution;

    std::vector<double>* get_weights() {
        return &_weights;
    }


    Exp3m_heap() = default;

    Exp3m_heap(int m, int k, double gamma) : _m(m), _k(k), _gamma(gamma)
    {
        _weights = std::vector<double>(k, 1);
        _distribution = Incremental_LSE_sum_heap(_weights);
        _last_probabilities.reserve(_k);
        //std::vector<double> power_weights(k, exp(_gamma / _k * ((1.0 / k)) - (1.0 / k)));
        //_power_weights = Incremental_sum_heap(power_weights);
        std::cout << _gamma << std::endl;
        max_weight = 1;
        //weight_sum = k;
    };
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
        //std::vector<int> choices;
        //choices.reserve(_k)
        //if (_uni(_random_gen) < _gamma) {

            //choices rand()%_k;

       // } else {
        std::vector<int> choices = _distribution.heap_sample(m);
        //}

        /*double sum_exp = 0;
        double mw = *max_element(_weights.begin(), _weights.end());
        for (int i = 0; i < _k; i++)
        {
            sum_exp += exp(_weights[i] - mw);
        }*/

        for (int i : choices) {
        //for (int i = 0; i < _k; i++) {
            //std::cout << _distribution.max_element() << " " << weight_sum << std::endl;
            double p = ( (1 - _gamma) * exp(_weights[i] - max_weight - log(_distribution.max_element()) ) + _gamma/ _k);

            //double p = (1 - _gamma)*(exp(_weights[i]-max_weight)/exp(_distribution.max_element()-max_weight))+ _gamma/ _k;

            //std::cout << p << " " << (1 - _gamma)*(exp(_weights[i]-max_weight)/exp(_distribution.max_element()-max_weight))+ _gamma/ _k << std::endl;
            //double p = ( (1 - _gamma) * (exp(_weights[i] - max_weight)/weight_sum ) + _gamma/ _k);
            _last_probabilities[i] = p;
        }

        //_last_probabilities = probabilities;
        return choices; //Incremental_sum_heap(probabilities).heap_sample(m); //_distribution.heap_sample(m);
    };
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards)
    {

        //std::cout << _distribution.max_element() << std::endl;
        for (int idx = 0; idx < indices.size(); idx++) {
            int i = indices[idx];
            //std::cout << rewards[idx] << std::endl;
            double old = _weights[i];
            /*if (_last_probabilities[i] >= ((1-_gamma)+(_gamma/_k))) {
                //std::cout << "trigger" << std::endl;
                continue;
            }*/
            //std::cout << rewards[idx] << " " << _last_probabilities[i] << " " << _gamma << std::endl;
            _weights[i] += _gamma * (rewards[idx] / _last_probabilities[i]) / _k; //implicit log

            //std::cout << i << " " << _weights[i] << _last_probabilities[i] << std::endl;
            //_power_weights.update(i, exp(_weights[i] ));
            if (_weights[i] > max_weight) {
                //Remove old
                /*weight_sum -= exp(old - max_weight);
                //Correct other weigths
                weight_sum *= exp(max_weight - _weights[i]);
                //Add new replacement
                weight_sum += 1;*/
                max_weight = _weights[i];
            } /*else {
                //Remove old
                weight_sum -= exp(old - max_weight);
                //Add replacement
                weight_sum += exp(_weights[i] - max_weight);
            }*/
            _distribution.update(i, _weights[i]);
        }
        //for (int idx = 0; idx < indices.size(); idx++) {
            //int i = indices[idx];
            //double p = ( (1 - _gamma) * exp(_weights[i] - max_weight - log(weight_sum) ) + _gamma/ _k);
            //_last_probabilities[i] = p;
            //double max_elm = _distribution.max_element()+(_distribution.probability_of_choice(i)-_last_probabilities[i]);
            //double corr_val = (_last_probabilities[i]-_last_probabilities[i]*(max_elm))/(_last_probabilities[i]-1);
            /*if (std::isinf(corr_val) || _last_probabilities[i]+corr_val > 1 ||_last_probabilities[i] == max_elm || _last_probabilities[i] == 1.0) {
                //std::cout << i << "  " << _last_probabilities[i] << "  " << corr_val << "   " << _distribution.max_element() <<"   "<< _distribution.probability_of_choice(i) << std::endl;
                //    _distribution.update(i, _gamma/_k);
                //_distribution.update(i, _last_probabilities[i]);
                cnt++;
                std::cout << cnt << " " << _last_probabilities[i] << " " << _last_probabilities[i]+corr_val << " " << _distribution.max_element() << std::endl;
                if (!std::isinf(corr_val) ) {
                    _distribution.update(i, _last_probabilities[i]);
                }
            } else {*/
                //std::cout << i << "  " << _last_probabilities[i] << "  " << corr_val << "   " << _distribution.max_element() <<"   "<< _distribution.probability_of_choice(i) << std::endl;

            //}
        //}
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
