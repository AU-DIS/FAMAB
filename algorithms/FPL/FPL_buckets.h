//
// Created by Mathias Ravn Tversted on 07/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPL_BUCKETS_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPL_BUCKETS_H

#include <queue>
#include <functional>


class FPL_buckets {
private:
    int _k;
    std::vector<double> _weights;
    std::exponential_distribution<double> _exponential_distribution;
    std::mt19937 _gen;
    double _eta;
    better_priority_queue::updatable_priority_queue<int, double> _q;
    int _counter;
    int _log_k;

public:
    FPL_buckets(int k, double eta) {
        _k = k;
        _eta = eta;
        _counter = 0;
        _log_k = (int) log2(k);

        _exponential_distribution = std::exponential_distribution<double>(_eta);
        _gen = random_gen();
        _weights = std::vector<double>(k, 0);
        for (auto &w: _weights) w += _exponential_distribution(_gen);
        _q = better_priority_queue::updatable_priority_queue<int, double>();
        for (int i = 0; i < k; i++) _q.push(i, _weights[i]);
    }

    int choose() {
        for (int i = 0; i < _log_k; i++) {
            _weights[_counter % _k] += _exponential_distribution(_gen);
            _q.update(_counter % _k, _weights[_counter %_k]);
            _counter++;
        }

        return _q.top().key;
    }
    void give_reward(int choice, double feedback) {
        _weights[choice] += feedback;
        _q.update(choice, _weights[choice]);
    }

};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_FPL_BUCKETS_H
