#include <iostream>

#include <algorithm>
#include <numeric>
#include <cmath>

#include "utils.h"

const unsigned int TARGET_SUM = 1000;

int main() {
    std::vector<std::vector<int>> things;
    std::vector<int> alphabet;
    std::generate_n(std::back_inserter(alphabet), 100, [n = 1] () mutable {return n++;});

    combs(alphabet, 100, things, {2, 2});

    for(const auto& thing : things) {
        for(const auto& ele : thing) {
            std::cout << ele << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}

