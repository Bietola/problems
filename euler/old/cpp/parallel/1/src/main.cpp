#include <iostream>
#include <future>

const size_t LIMIT = 1'000'000'000;

std::future<long long> divisibleBy(long long divisor, size_t limit) {
    return std::async(std::launch::async, [limit, divisor] {
        long long sum = 0;
        for(long long j = divisor; j < limit; j += divisor) {
            sum += j;
        }
        return sum;
    });
}

int main() {
    auto divisibleBy3  = divisibleBy( 3, LIMIT);
    auto divisibleBy5  = divisibleBy( 5, LIMIT);
    auto divisibleBy15 = divisibleBy(15, LIMIT);

    std::cout << (divisibleBy3.get() + divisibleBy5.get() - divisibleBy15.get()) << "\n";
                  
    // return
    return 0;
}
