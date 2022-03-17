//
// Created by Mathias Ravn Tversted on 10/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_EXP3VECTORWEIGHTSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_EXP3VECTORWEIGHTSTRATEGY_H
#include <vector>
#include <random>
#include "../../utilities/random_gen.h"


class Exp3VectorWeightStrategy {
private:
    int sample();
    std::vector<double> _probabilities;
    std::mt19937 _random_gen = random_gen();

public:
    std::vector<double> _weights;
    Exp3VectorWeightStrategy(size_t k, double gamma);
    int choose();
    void update_weight(size_t index, double weight);
    std::vector<double> get_weights();
    int _k;
    double _gamma;
    double last_drawn_probability;
    double last_drawn_weight;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_EXP3VECTORWEIGHTSTRATEGY_H