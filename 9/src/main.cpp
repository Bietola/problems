#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

const unsigned int TARGET_SUM = 1000;

int main() {
    for(int a = 1;; ++a) {
        for(int b = a;; ++b) {
            for(int c = 1;; ++c) {
                if(std::pow(a, 2) + std::pow(b, 2) == std::pow(c, 2) &&
                   a + b + c == TARGET_SUM) {
                    std::cout << "found 'em: " << a << ", " << b << ", " << c << std::endl;
                    return 0;
                }
            }
        }
    }

    std::cout << "did not find 'em..." << std::endl;
    return -1;
}

