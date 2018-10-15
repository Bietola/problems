#include <iostream>
#include <chrono>
#include <thread>
#include <numeric>
#include <future>

#include "utils/void.h"
#include "utils/execution_info.h"

// function to test parallelism
template <class T>
T random_accumulation(size_t n, size_t max = 1'000,
                         bool doReserve = false) {
    std::vector<T> v;
    if(doReserve) v.reserve(n);

    std::generate_n(std::back_inserter(v), n, [max] {
        return rand() % max;
    });

    return std::accumulate(std::begin(v), std::end(v), 0);
}

// MAIN
int main() {
    namespace chrono = std::chrono;

    auto info = record_execution([] {
            const auto ASYNC_POLICY = std::launch::deferred;
            // with:    4859, 4684, 5450
            // without: 1317, 1327, 1324, 1338, 1321
            // both:    5705, 5495
            auto result1 = std::async(ASYNC_POLICY,
                                      &random_accumulation<int>, 10'000'000,
                                      1'000, false);
            auto result2 = std::async(ASYNC_POLICY,
                                      &random_accumulation<int>, 10'000'000,
                                      1'000, false);
            return result1.get() + result2.get();
    });
    // TODO: maybe use deduction guide to make this return the withheld value
    auto result = info.get_result();

    std::cout << "result: " << result << "\n";
    std::cout << "time elapsed: " << 
        chrono::duration_cast<chrono::milliseconds>(
            info.get_execution_time()
        ).count() << "\n";

    return 0;
}
