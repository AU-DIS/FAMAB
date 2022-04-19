//
// Created by Mathias Ravn Tversted on 11/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_RV_H
#define EFFICIENT_MULTI_ARMED_BANDITS_RV_H
class RV {
public:
    std::vector<double> estimate(size_t index, double feedback, std::vector<double> &weights, double eta) {
        std::vector<double> estimators;
        estimators.reserve(weights.size());

        for (size_t i = 0; i <weights.size(); i++) {
            double indicator = i == index? 1 : 0;
            double B = weights[i] >= (eta * eta) ? 1.0/2.0 : 0;
            double estimator = (indicator * ((1 - feedback) - B))/weights[i] + B;
            estimators.push_back(estimator);
        }
        return estimators;
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_RV_H
