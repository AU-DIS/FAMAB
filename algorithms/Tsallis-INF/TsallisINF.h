//
// Created by Mathias Ravn Tversted on 22/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_TSALLISINF_H
#define EFFICIENT_MULTI_ARMED_BANDITS_TSALLISINF_H


class TsallisINF {
public:
    explicit TsallisINF(int K);
    double compute_eta(int t);
    std::vector<double> newtons_method_weights(std::vector<double> &losses, double eta);
    int choose();
    void give_reward(size_t index, double feedback);
    std::vector<double> _weights;
private:
    std::vector<double> cumulative_losses;
    int _t = 1;
    double _x = 1;
    double _eta;
    double IW(size_t index, double feedback);

    std::vector<double> RV(size_t index, double feedback);
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_TSALLISINF_H
