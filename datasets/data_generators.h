//
// Created by Mathias Ravn Tversted on 05/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_DATA_GENERATORS_H
#define EFFICIENT_MULTI_ARMED_BANDITS_DATA_GENERATORS_H
#include "dataset.h"

std::vector<std::discrete_distribution<int>> create_distributions(int k) {
    std::vector<std::discrete_distribution<int>> distributions(k);

    std::normal_distribution<double> gamma_distribution(1.2, 1);


    auto gen = random_gen();

    std::vector<double> probabilities(k);
    for (int i = 0; i < k; i++) {
        double p = gamma_distribution(gen);
        probabilities[i] = p;
    }

    double max_p = *std::max_element(probabilities.begin(), probabilities.end());
    double min_p = *std::min_element(probabilities.begin(), probabilities.end());

    for (int i = 0; i < k; i++) {
        probabilities[i] += min_p;
        probabilities[i] /= (max_p + min_p);
        std::vector<double> weights = {probabilities[i], 1. - probabilities[i]};
        std::discrete_distribution<int> dist(weights.begin(), weights.end());
        distributions[i] = dist;
    }
    return distributions;
}


std::vector<std::discrete_distribution<int>>
create_distributions(int k, int optimal_start, int optimal_end, double delta) {
    std::vector<std::discrete_distribution<int>> distributions(k);
    auto gen = random_gen();

    std::normal_distribution<double> suboptimal_distribution(1 - delta, 4);
    std::discrete_distribution<int> optimal_distribution({1 - delta, delta});

    std::vector<double> probabilities(k);

    std::vector<double *> suboptimal_probabilities;

    for (int i = 0; i < k; i++) {
        if (i >= optimal_start && i <= optimal_end) {
            probabilities[i] = delta;
        } else {
            double p = suboptimal_distribution(gen);
            probabilities[i] = p;
            suboptimal_probabilities.push_back(&p);
        }
    }

    double max_p = 0;
    double min_p = k + 1;
    for (double *p: suboptimal_probabilities) {
        if (*p < min_p) min_p = *p;
        else if (*p >= max_p) max_p = *p;
    }
    for (double *p: suboptimal_probabilities) {
        *p /= (min_p + max_p);
    }

    for (int i = 0; i < k; i++) {
        std::vector<double> weights = {1 - probabilities[i], probabilities[i]};
        std::discrete_distribution<int> dist(weights.begin(), weights.end());
        distributions[i] = dist;
    }

    return distributions;
}

std::vector<std::vector<double>> stochastically_constrained_adversarial(int k, double delta, int rounds, double gap) {
    auto gen = random_gen();


    std::discrete_distribution<int> first_optimal({0, 1});
    std::discrete_distribution<int> first_suboptimal({1 - delta, delta});

    std::discrete_distribution<int> second_optimal({1 - delta, delta});
    std::discrete_distribution<int> second_suboptimal({0, 1});


    auto arm_picker_weights = std::vector<int>(k, 1);
    std::discrete_distribution<int> optimal_arm_picker(arm_picker_weights.begin(), arm_picker_weights.end());


    std::vector<std::vector<double>> data_matrix;
    data_matrix.reserve(k);

    for (int i = 0; i < k; i++) {
        std::vector<double> row(rounds);
        data_matrix.push_back(row);
    }

    auto current_optimal = first_optimal;
    auto current_suboptimal = first_suboptimal;
    auto is_first = true;
    int multiple = 1;
    int optimal_arm = 1;
    for (int round = 0; round < rounds; round++) {
        double threshold = pow(gap, multiple);
        if (round > threshold) {
            optimal_arm = optimal_arm_picker(gen);
            current_optimal = is_first ? second_optimal : first_optimal;
            current_suboptimal = is_first ? second_suboptimal : second_optimal;
            is_first = !is_first;
            multiple++;
        }

        for (int arm = 0; arm < k; arm++) {
            data_matrix[arm][round] = current_suboptimal(gen);
        }
        data_matrix[optimal_arm][round] = current_optimal(gen);
    }
    return data_matrix;
}


class StochasticDataset: public Dataset{
private:
    int _k{};
    int _rounds{};
    double _lambda{};
    std::mt19937 _gen;

public:
    StochasticDataset() = default;
    StochasticDataset(int k, int rounds, double lambda)
    {
        _k = k;
        _rounds = rounds;
        _lambda = lambda;
        _gen = random_gen();

    }

    std::vector<std::vector<double>> generate() {
        std::vector<std::vector<double>> data_matrix;
        data_matrix.reserve(_k);



        for (int arm = 0; arm < _k; arm++) {
            double p = _lambda - (((double) arm)/_k);
            if (p < 0) p *= -1;
            std::discrete_distribution<int> bernoulli({1 - p, p});
            std::vector<double> row;
            row.reserve(_rounds);
            for (int round = 0; round < _rounds; round++) {
                double v = bernoulli(_gen);
                row.push_back(v);
            }
            data_matrix.push_back(row);
        }
        return data_matrix;
    }
};


class StochasticallyConstrainedDataset: public Dataset {
private:
    int _k{};
    int _rounds{};
    double _gap{};
    double _delta{};


public:
    StochasticallyConstrainedDataset() = default;
    StochasticallyConstrainedDataset(int k, int rounds, double gap, double delta) {
        _k = k;
        _rounds = rounds;
        _gap = gap;
        _delta = delta;
    }

    std::vector<std::vector<double>> generate() {
        int k = _k;
        int rounds = _rounds;
        double gap = _gap;
        double delta = _delta;
        auto gen = random_gen();
        std::vector<std::vector<double>> data_matrix;
        data_matrix.reserve(k);


        auto distributions = create_distributions(k, 0, int(pow(gap, 1)), delta);
        for (int i = 0; i < k; i++) {
            std::vector<double> row(rounds, 1);
            data_matrix.push_back(row);
        }
        bool even = true;


        int multiple = 1;
        for (int i = 0; i < rounds; i++) {
            double threshold = pow(gap, multiple);
            if (i > threshold) {

                distributions = create_distributions(k, (int) pow(gap, multiple), (int) pow(gap, multiple + 1), delta);
                even = !even;
                multiple++;
            }

            for (int arm = 0; arm < k; arm++) {
                data_matrix[arm][i] = distributions[arm](gen);
            }
        }

        return data_matrix;
    }
};


class Mod2Dataset: public Dataset {
private:
    int _k{};
    int _rounds{};
    double _gap{};

public:
    Mod2Dataset() = default;
    Mod2Dataset(int k, int rounds, double gap) {
        _k = k;
        _rounds = rounds;
        _gap = gap;
    }
    std::vector<std::vector<double>> generate() {
        int k = _k;
        int rounds = _rounds;
        double gap = _gap;
        std::vector<std::vector<double>> data_matrix;
        data_matrix.reserve(k);
        for (int i = 0; i < k; i++) {
            std::vector<double> row(rounds, 0);
            data_matrix.push_back(row);
        }
        bool even = true;

        int multiple = 1;
        for (int i = 0; i < rounds; i++) {
            double threshold = pow(gap, multiple);
            if (i > threshold) {
                even = !even;
                multiple++;
            }
            for (int arm = 0; arm < k; arm++) {
                data_matrix[arm][i] = even ? arm % 2 : (arm + 1) % 2;
            }
        }
        return data_matrix;
    }

};



#endif //EFFICIENT_MULTI_ARMED_BANDITS_DATA_GENERATORS_H
