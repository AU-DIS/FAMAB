//
// Created by Mathias Ravn Tversted on 10/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H
#include <vector>
#include <random>


class VectorWeightStrategy {
private:
    int sample();
    std::vector<double> _weights;
    std::vector<double> _probabilities;
    std::mt19937 _random_gen;

public:
    VectorWeightStrategy(int k, double gamma);
    int choose();
    void update_weight(int index, double weight);
    std::vector<double> get_weights();
    int _k;
    double _gamma;
    double last_drawn_probability;
    double last_drawn_weight;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_VECTORWEIGHTSTRATEGY_H