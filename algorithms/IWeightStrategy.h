//
// Created by Kristoffer Strube on 08-02-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_IWEIGHTSTRATEGY_H
#define EFFICIENT_MULTI_ARMED_BANDITS_IWEIGHTSTRATEGY_H

class IWeightStrategy {
public:
    virtual int choose();
    virtual void UpdateWeight(int index, double weight);
};

#endif //EFFICIENT_MULTI_ARMED_BANDITS_IWEIGHTSTRATEGY_H
