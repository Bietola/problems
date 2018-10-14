#include <iostream>
#include <chrono>
#include <thread>
#include <numeric>
#include <future>

#include "utils/void.h"

template <class Result, class TimeRep = double>
struct execution_info {
    private:
        using Duration = std::chrono::duration<TimeRep>;

        Result _result;
        Duration _execution_time;

    public:
        // TODO: find a way to remove this
        // TODO: optmize for move semantics
        execution_info(const Result& result,
                       const Duration& execution_time):
            _result(result), _execution_time(execution_time) {}

        // getters
        Result get_result() const { return _result; }
        auto get_execution_time() const { return _execution_time; }
};

template <class Fun, class... Args,
          class Result = utl::void_invoke_result_t<Fun, Args...>>
execution_info<Result>
record_execution(Fun&& fun, Args&&... args) {
    namespace chrono = std::chrono;

    // start recording time
    auto startTime = chrono::system_clock::now();

    // execute function
    //     TODO: write template deduction guide for void 
    Result result = utl::void_invoke(std::forward<Fun>(fun),
                                std::forward<Args>(args)...);

    auto endTime = chrono::system_clock::now();
    auto executionTime = endTime - startTime;

    // return function execution info
    return {result, executionTime};
}

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
