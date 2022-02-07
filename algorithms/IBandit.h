//
// Created by Mathias Tversted on 06/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_IBANDIT_H
#define EFFICIENT_MULTI_ARMED_BANDITS_IBANDIT_H

class IBandit {
public:
    virtual void export_weights(std::string path) {};
    virtual void give_reward(int choice, double reward) {}
    virtual int draw() { return 0; }
    virtual ~IBandit()= default;
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_IBANDIT_H
