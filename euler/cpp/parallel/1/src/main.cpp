#include <iostream>
#include <future>

const size_t LIMIT = 1'000;

int main() {
    // calculate multiples of 3
    auto sum3 = std::async(std::launch::async, [] {
        int sum = 0;
        for(int j = 3; j < LIMIT; j += 3) {
            sum += j;
        }
        return sum;
    });

    // calculate multiples of 5 and not of 3
    auto sum5 = std::async(std::launch::async, [] {
        int sum = 0;
        for(int j = 5; j < LIMIT; j += 5) {
            if(j % 3 != 0)
                sum += j;
        }
        return sum;
    });

    // sum things up
    int sum = sum3.get() + sum5.get();

    // answer
    std::cout << sum << "\n";
   
    return 0;
}
