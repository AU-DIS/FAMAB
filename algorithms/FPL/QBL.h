//
// Created by Mathias Ravn Tversted on 07/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_QBL_H
#define EFFICIENT_MULTI_ARMED_BANDITS_QBL_H

#include "../../utilities/updateable_priority_queue.h"

class QBL
{
private:
    int _k;
    std::exponential_distribution<double> _exponential_distribution;
    std::mt19937 _gen;
    double _eta;
    std::vector<int> _priorities;
    std::vector<double> cumulative_rewards;
    better_priority_queue::updatable_priority_queue<int, int> _q;
    int _counter;
    int _logk;
    int _round;
    int rounds_leader_optimal;
    double F;

public:
    QBL() = default;

    std::vector<double> *get_weights()
    {
        auto ret = new std::vector<double>();
        for (auto v : _priorities)
            ret->push_back(v);
        return ret;
    }

    QBL(const QBL &prototype)
    {
        _k = prototype._k;
        _eta = prototype._eta;
        _counter = 0;
        _round = 0;
        F = 0;

        //_logk = (int) log2(k);
        _logk = prototype._k;
        //_logk = 2;

        _exponential_distribution = std::exponential_distribution<double>(_eta);
        _gen = random_gen();
        _priorities = std::vector<int>();
        cumulative_rewards = std::vector<double>(_k, 0);

        _q = better_priority_queue::updatable_priority_queue<int, int>();
        for (int i = 0; i < _k; i++)
        {
            _priorities.push_back(i);
            _q.push(i, i);
        }
        rounds_leader_optimal = 0;
    }

    QBL(int k, double eta)
    {
        _k = k;
        _eta = eta;
        _counter = 0;
        _round = 0;
        F = 0;
        cumulative_rewards = std::vector<double>(_k, 0);

        _logk = (int)log2(k);
        //_logk = k;
        //_logk = 2;

        _exponential_distribution = std::exponential_distribution<double>(_eta);
        _gen = random_gen();
        _priorities = std::vector<int>();

        _q = better_priority_queue::updatable_priority_queue<int, int>();
        for (int i = 0; i < k; i++)
        {
            _priorities.push_back(i);
            _q.push(i, i);
        }
        rounds_leader_optimal = 0;
    }

    std::vector<int> choose(int m)
    {

        for (int i = 0; i < _logk; i++)
        {
            int priority_delta = (int)_exponential_distribution(_gen);
            _priorities[i] = min(_k, _priorities[i] + priority_delta);
            _q.update(i, _priorities[i]);
            _counter++;
        }
        std::vector<int> choices(m, 0);
        for (int i = 0; i < m; i++)
        {
            choices[i] = _q.top().key;
            _q.pop();
        }
        for (int i = 0; i < m; i++)
        {
            _q.push(choices[i], _priorities[choices[i]]);
        }
        /*
        for (int i = 0; i < _logk; i++)
        {
            int priority_delta = (int)_exponential_distribution(_gen);
            _priorities[i] = min(_k, _priorities[i] + priority_delta);
            _q.update(i, _priorities[i]);
            _counter++;
        }
        std::vector<int> choices(m, 0);
        for (int i = 0; i < m; i++)
        {
            choices[i] = _q.top().key;
            _q.pop();
        }
        for (int i = 0; i < m; i++)
        {
            _q.push(choices[i], _priorities[choices[i]]);
        }
*/
        return choices;
    }
    void give_reward(std::vector<int> &indices, std::vector<double> &rewards)
    {

        for (int i = 0; i < indices.size(); i++)
        {
            int choice = indices[i];
            int reward = rewards[i];
            cumulative_rewards[choice] += reward;
            F += reward;
            if (reward == 0)
            {
                int new_position = (int)(cumulative_rewards[choice] / F) * _k;
                new_position = std::min(new_position, _k - 1);
                _priorities[choice] = new_position;
                _q.update(choice, _priorities[choice]);
                //_priorities[choice] = 0;
                //_q.update(choice, _priorities[choice]);
            }
        }

        /*
                for (int i = 0; i < indices.size(); i++)
                {
                    auto feedback = rewards[i];
                    if (feedback == 0)
                    {
                        _priorities[indices[i]] = 0;
                        rounds_leader_optimal = 0;
                        //_q.pop();
                        _q.update(indices[i], _priorities[indices[i]]);
                    }
                }
                */
    }

    int choose()
    {
        for (int i = 0; i < _logk; i++)
        {
            int priority_delta = (int)_exponential_distribution(_gen);
            _priorities[i] = min(_k, _priorities[i] + priority_delta);
            _q.update(i, _priorities[i]);
            _counter++;
        }
        return _q.top().key;
    }
    void give_reward(int choice, double feedback)
    {
        if (feedback == 0)
        {
            _priorities[choice] = rounds_leader_optimal;
            rounds_leader_optimal = 0;
            _q.pop();
            _q.push(choice, _priorities[choice]);
        }
        else
        {
            rounds_leader_optimal = min(rounds_leader_optimal + 1, _k - 2);
            // std::cout << std::to_string(rounds_leader_optimal) + "\n";
        }
    }
};

#endif // EFFICIENT_MULTI_ARMED_BANDITS_QBL_H
