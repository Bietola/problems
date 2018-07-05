#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

const unsigned int TARGET_SUM = 1000;

int main() {
    size_t x = 1, y = 1;
    for(float a = 1;;++x) {
        for(float b = a + 1;;++b) {
            auto c = std::sqrt(std::pow(a, 2)) +  (std::pow(b, 2));
            auto sum = a + b + c;
            if(sum > TARGET_SUM) {
                break;
            }
            if(std::floor(c) == c && a + b + c == TARGET_SUM) {
                std::cout << "found 'em: (" << a << ", " << b << ", " << c << ")" << std::endl;
                return 0;
            }
        }
    }

    std::cout << "did not find 'em..." << std::endl;
    return 1;
}
