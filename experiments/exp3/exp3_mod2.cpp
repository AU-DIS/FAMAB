//
// Created by Mathias Ravn Tversted on 03/02/2022.
//
#include <iostream>
#include "../../algorithms/Exp3.h"
#include <benchmark/benchmark.h>

static void run_exp3_mod2_bandit(double gamma, int K, int iterations) {
    Exp3 bandit = Exp3(gamma, K);
    srand(time(NULL));
    int no_correct = 0;
    int no_wrong = 0;
    for (int i = 0; i < iterations; i++) {
        int c = bandit.draw();
        if (c % 2 == 0) {
            no_correct ++;
            bandit.give_reward(c, 1);
        }
        else {
            no_wrong ++;
            bandit.give_reward(c, 0);
        }
    }
    //TODO: learn how to use format strings in C++
    std::cout << "Number correct: ";
    std::cout << int(100*no_correct/iterations);
    std::cout << "%";
    std::cout << "\t Number wrong: ";
    std::cout << int(100*no_wrong/iterations);
    std::cout << "%";

}
static void BM_Exp3(benchmark::State& state) {
    //run_exp3_mod2_bandit();
}


