//
// Created by Mathias Ravn Tversted on 28/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_RBA_H
#define EFFICIENT_MULTI_ARMED_BANDITS_RBA_H

#include "vector"
#include "set"

template<typename Bandit>
class RBA {
private:
    std::vector<Bandit> _bandits;
    int _num_bandits;
    double _threshold;

public:
    RBA(int num_bandits, int K, double threshold, Bandit &prototype)
            : _num_bandits(num_bandits), _threshold(threshold) {
        for (int i = 0; i < _num_bandits; i++) {
            auto b = Bandit(prototype);
            _bandits.push_back(b);
        }
    }
    std::vector<int> choose() {
        std::vector<int> choices;
        std::set<int> c_choices;
        for (auto b: _bandits) {
            int choice = _num_bandits + 1;
            do {
                choice = b.choose();
            } while (c_choices.count(choice));
            c_choices.insert(choice);
            choices.push_back(choice);
        }
        return choices;
    }

    void give_reward(std::vector<int> &indices, std::vector<double> &rewards) {
        bool encountered_one = false;
        for (int i = 0; i < indices.size(); i++) {
            int index = indices[i];
            auto v = rewards[i];
            v = (v >= _threshold && !encountered_one) ? 1.0 : 0.0;
            encountered_one = ((v == 1) | encountered_one);
            _bandits[i].give_reward(index, v);
        }
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_RBA_H
