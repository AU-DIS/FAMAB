//
// Created by Mathias Ravn Tversted on 07/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_QBL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_QBL_H

#include "../../utilities/updateable_priority_queue.h"

class QBL {
private:
    int _k;
    std::exponential_distribution<double> _exponential_distribution;
    std::mt19937 _gen;
    double _eta;
    std::vector<int> _priorities;
    better_priority_queue::updatable_priority_queue<int, int> _q;
    int _counter;
    int _log_k;
    int _round;

public:
    QBL(int k, double eta) {
        _k = k;
        _eta = eta;
        _counter = 0;
        _round = 0;

        //_log_k = (int) log2(k);
        _log_k = k;
        //_log_k = 2;

        _exponential_distribution = std::exponential_distribution<double>(_eta);
        _gen = random_gen();
        _priorities = std::vector<int>();

        _q = better_priority_queue::updatable_priority_queue<int, int>();
        for (int i = 0; i < k; i++) {
            _priorities.push_back(i);
            _q.push(i, i);
        }
    }


    std::vector<int> choose(int m) {
        std::vector<int> choices(m, 0);
        for (int i = 0; i < m; i++) {
            choices[i] = _q.top().key;
            _q.pop();
        }
        for (int i = 0; i < m; i++) {
            _q.push(choices[i], _priorities[choices[i]]);
        }
        return choices;
    }
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards) {
        for (int i = 0; i < indices.size(); i++) {
            int choice = indices[i];
            if (rewards[i] == 0) {
                _priorities[choice] = 0;
                _q.update(choice, 0);
            }
        }
    }

    int choose() {
        for (int i = 0; i < _log_k; i++) {
            int priority_delta = (int) _exponential_distribution(_gen);
            _priorities[i] = min(_k, _priorities[i] + priority_delta);
            _q.update(i, _priorities[i]);
            _counter++;
        }
        return _q.top().key;
    }
    void give_reward(int choice, double feedback) {
        if (feedback == 0) {
            _priorities[choice] = 0;
            _q.pop();
            _q.push(choice, _priorities[choice]);
        }
    }

};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_QBL_H
