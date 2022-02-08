//
// Created by Mathias Ravn Tversted on 08/02/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_IDATASET_H
#define EFFICIENT_MULTI_ARMED_BANDITS_IDATASET_H

class IDataset {
public:
    virtual double feedback(int choice) = 0;
    int k = 0;
    int reward_max = 0;
    int reward_min = 0;
};


#endif //EFFICIENT_MULTI_ARMED_BANDITS_IDATASET_H
