//
// Created by Kristoffer Strube on 17-02-2022.
//

#include "DepRoundALIASStrategy.h"
#include "random"
#include "../../utilities/random_gen.h"

std::vector<int> DepRoundALIASStrategy::dependent_weighted_choices(std::vector<double> probabilities, int k) {
    std::mt19937 rng = random_gen();
    std::uniform_real_distribution<double> uniform(0, 1);

    int K = probabilities.size();

    std::vector<int> candidates;
    candidates.reserve(K);
    for (int i = 0; i < K; i++) candidates.push_back(i);

    std::vector<int> return_indices;
    return_indices.reserve(k);

    while (candidates.size() > 1) {
        int i = candidates.back();
        candidates.pop_back();
        int j = candidates.back();
        candidates.pop_back();

        double alpha = 1 - probabilities[i] < probabilities[j] ? 1 - probabilities[i] : probabilities[j];
        double beta = probabilities[i] < 1 - probabilities[j] ? probabilities[i] : 1 - probabilities[j];

        double r = uniform(rng);

        if (r > beta / (alpha + beta)) {
            probabilities[i] += alpha;
            probabilities[j] -= alpha;
        } else {
            probabilities[i] -= beta;
            probabilities[j] += beta;
        }

        if (probabilities[i] >= 0.99999 && probabilities[i] <= 1) return_indices.push_back(i);
        else if (probabilities[i] > 0.0000000000) candidates.push_back(i);

        if (probabilities[j] >= 0.99999 && probabilities[j] <= 1) return_indices.push_back(j);
        else if (probabilities[j] > 0.0000000000) candidates.push_back(j);

    }

    return return_indices;
};