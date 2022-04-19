//
// Created by Mathias Tversted on 12/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_TSALLIS_RV_H
#define EFFICIENT_MULTI_ARMED_BANDITS_TSALLIS_RV_H

#include <random>

class Tsallis_RV {
private:
    int _t;
    double _eta;
    std::mt19937 _rg;
    double _x;
    std::vector<double> _weights;
    std::vector<double> _cumulative_losses;
    int _k;

    double compute_eta(int t) {
        _eta = 1 / sqrt(std::max(1, t));
        return _eta;
    }

    /// This assumes alpha = 1/2
    std::vector<double> newtons_method_weights(std::vector<double> &losses, double eta) {

        std::vector<double> weights;
        double x_previous = _x;
        double x_estimated = _x;
        weights.reserve(losses.size());


        for (int i = 0; i < losses.size(); i++) weights.push_back(0);

        do {
            x_previous = x_estimated;
            for (int i = 0; i < losses.size(); i++) weights[i] = 4 * pow((eta * (losses[i] - x_previous)), -2);
            double w_sum_powered = 0;
            double w_sum = 0;
            for (auto w: weights) {
                w_sum_powered += pow(w, (3 / 2));
                w_sum += w;
            }
            x_estimated = x_previous - (w_sum - 1) / (eta * w_sum_powered);
        } while (std::min(x_previous, x_estimated) / std::max(x_previous, x_estimated) >= 1.1);
        _x = x_estimated;
        return weights;
    }


public:
    explicit Tsallis_RV(int k) {
        _cumulative_losses = std::vector<double>(k, 0);
        _rg = random_gen();
        _t = 1;
        _x = 1;
        _k = k;
        _eta = 1;
    }

    int choose() {
        _weights = newtons_method_weights(_cumulative_losses, compute_eta(_t));
        std::discrete_distribution<> d(_weights.begin(), _weights.end());

        int s = d(_rg);
        _t += 1;
        return s;
    }

    void give_reward(size_t index, double feedback) {
        for (size_t i = 0; i < _k; i++) {
            double indicator = i == index ? 1 : 0;
            double B = _weights[i] >= (_eta * _eta) ? 1.0 / 2.0 : 0;
            double estimator = (indicator * ((1 - feedback) - B)) / _weights[i] + B;
            _cumulative_losses[i] += estimator;
        }
    }
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_TSALLIS_RV_H
