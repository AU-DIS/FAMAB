#include <iostream>
#include "algorithms/Exp3.h"

int main() {
    Exp3 bandit = Exp3(0.01, 1000);
    srand(time(NULL));
    int no_correct = 0;
    int no_wrong = 0;
    int iterations = 100000;
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
    return 0;
}
