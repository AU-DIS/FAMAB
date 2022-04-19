//
// Created by Mathias Ravn Tversted on 05/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPL_HASH_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPL_HASH_H

#include "../../utilities/random_gen.h"
#include "../../utilities/updateable_priority_queue.h"
class FPL_hash {
private:
    int _k;
    std::vector<double> _weights;
    std::exponential_distribution<double> _exponential_distribution;
    std::mt19937 _gen;
    double _eta;
    std::vector<double>* _presampled_noise;
    int _number_to_presample;
    double _a;
    double _b;


private:
    int mersenne_8 = 2147483647;
    unsigned int hash(double w) {
        auto r =  (((unsigned int) (_a * w + _b)) % mersenne_8) % _number_to_presample;
        return r;
    }

public:
    FPL_hash(int k, double eta, int rounds) {
        _k = k;
        _eta = eta;
        _exponential_distribution = std::exponential_distribution<double>(_eta);
        _gen = random_gen();
        _weights = std::vector<double>(k, 0);
        for (auto &w : _weights) w += _exponential_distribution(_gen);


        _number_to_presample = rounds;
        _presampled_noise = new std::vector<double>;
        _presampled_noise->reserve(_number_to_presample);
        for (int i = 0; i < _number_to_presample; i++) {
            _presampled_noise->push_back(_exponential_distribution(_gen));
        }
        //for (auto w : *_presampled_noise) std::cout << w << ",";


        std::uniform_real_distribution<double> uni (0.0,1.0);

        _a = uni(_gen) * _number_to_presample;
        _b = uni(_gen) * _number_to_presample;

    }

    virtual ~FPL_hash() {
        free(_presampled_noise);
    }

    int choose() {
        for (auto &w: _weights) {
            auto h = hash(w);
            unsigned int index = h % _number_to_presample;
            w += (*_presampled_noise)[index];
            //std::cout << (*_presampled_noise)[index] << ",";
        }
        int max_index = 0;
        double max_element = 0;

        for (int i = 0; i < _k; i++) {
            if (_weights[i] > max_element) {
                max_index = i;
                max_element = _weights[i];
            }
        }
        return max_index;
    }
    void give_reward(int choice, double feedback) {
        _weights[choice] += feedback;
    }

};



#endif //EFFICIENT_MULTI_ARMED_BANDITS_FPL_HASH_H
