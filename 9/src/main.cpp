#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "utils.h"

const unsigned int TARGET_SUM = 1000;

void tripletsTargetSum(int target, std::vector<std::vector<int>>& result) {
    assert(target >= 3); 

    std::vector<int> alphabet;
    std::generate_n(std::back_inserter(alphabet), target - 2,
        [n = 1] () mutable {return n++;});

    combs(alphabet, target, result, {2, 2});

    result.erase(
        std::remove_if(result.begin(), result.end(), [] (const auto& ele) {
            auto sum = double(std::pow(ele[0], 2) + std::pow(ele[1], 2));
            return std::floor(std::sqrt(sum)) != std::sqrt(sum);
        }),
        result.end()
    );
}

int main() {
    std::vector<std::vector<int>> things;
    
    for(const auto& thing : things) {
        for(const auto& ele : thing) {
            std::cout << ele << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}

