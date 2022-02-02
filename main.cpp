#include <iostream>
#include "algorithms/Exp3.h"

int main() {
    Exp3 bandit = Exp3(0.7, 100);
    srand(time(NULL));
    for (int i = 0; i < 7000; i++) {
        int c = bandit.draw();
        std::cout << c;
        std::cout << "\n";
        if (c % 2 == 0) {
            bandit.give_reward(c, 1);
        }
        else {
            bandit.give_reward(c, 0);
        }

    }
    return 0;
}
