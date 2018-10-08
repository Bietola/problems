#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <numeric>

const unsigned int TARGET = 1000;

int main() {
    // do it!
    for(float a = 1; a <= TARGET - 2; ++a) {
        for(float b = a; b <= TARGET - 2; ++b) {
            float c = std::sqrt(std::pow(a, 2) + std::pow(b, 2));
            if(c == std::floor(c) && a + b + c == TARGET) {
                std::cout << "found it! " << a << "*" << b << "*" << c << " = " << a*b*c << std::endl;
                return 0;
            }
        }
    }
    
    // failure
    return -1;
}

