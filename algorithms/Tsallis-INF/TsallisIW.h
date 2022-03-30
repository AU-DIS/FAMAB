//
// Created by Mathias Ravn Tversted on 11/03/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_TSALLISIW_H
#define EFFICIENT_MULTI_ARMED_BANDITS_TSALLISIW_H

class TsallisIW {
public:
    std::vector<double> estimate(size_t index, double feedback, std::vector<double> &weights, double eta) {
        auto ret = std::vector<double>(weights.size(), 0);
        ret[index] = feedback/weights[index];
        return ret;
    }
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_TSALLISIW_H
