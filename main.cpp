#include "datasets/Dataset_movielens.h"
#include "algorithms/Exp3Bandit/Exp3RewardStrategy.h"
#include "algorithms/Exp3Bandit/Exp3VectorWeightStrategy.h"
#include "utilities/weight_exporter.cpp"
#include "algorithms/Exp3Bandit/Exp31.h"
#include "datasets/debug_simple_adversarial.h"

int main() {
    //auto d = Dataset_movielens("/Users/mrt/repos/efficient-multi-armed-bandits/datasets/data_directory/movielens.csv");
    int K = 10;
    int round_factor = 1000;
    int rounds = K * round_factor;

    //auto d = debug_simple_stochastic(K, rounds);
    Exp3VectorWeightStrategy ws(K, 0.1);
    Exp3RewardStrategy rs(ws);
    //Exp3Bandit banditmand(ws, rs);
    Exp31 b(ws, rs);

    //TsallisINF b(K);
    /*
    FPLVectorWeightStrategy ws(K);
    NaiveRandomGenStrategy rs(K, 0.2);
    FPL b(ws, rs);
    */

}