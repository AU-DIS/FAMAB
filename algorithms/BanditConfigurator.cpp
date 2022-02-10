//
// Created by Mathias Ravn Tversted on 10/02/2022.
//


#include "VectorWeightStrategy.h"
#include "Exp3RewardStrategy.h"
#include "Exp3Bandit.h"

static Exp3Bandit *standard_exp3(int k, double gamma) {
    auto vws = new VectorWeightStrategy(k, gamma);
    auto exp3rs = new Exp3RewardStrategy(vws);
    return new Exp3Bandit(vws, exp3rs);
}
