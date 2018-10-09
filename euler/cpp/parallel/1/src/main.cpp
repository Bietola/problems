#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <functional>
#include <tuple>
#include <numeric>
#include <thread>
#include <chrono>
#include <optional>

struct void_type { };

template <class T>
struct type_of { using type = T; };

template <class Fun, class... Args>
struct void_invoke_result : std::invoke_result<Fun, Args...> {};

template <class Fun, class... Args>
struct void_invoke_result<void> : type_of<void_type> {};

template <class T>
using void_invoke_result_t = typename void_invoke_result<T>::type;

template <class Fun, class... Args,
          class Result = void_invoke_result_t<Fun, Args...>>
Result void_invoke(Fun&& fun, Args&&... args) {
    // TODO: maybe add macro to avoid repetition of std::invoke
    if constexpr(std::is_void_v<Result>) {
        std::invoke(std::forward<Fun>(fun),
                    std::forward<Args>(args)...);
        return {};
    }
    else {
        return std::invoke(std::forward<Fun>(fun),
                           std::forward<Args>(args)...);
    }
}

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
          class Result = void_invoke_result_t<Fun, Args...>>
execution_info<Result>
record_execution(Fun&& fun, Args&&... args) {
    namespace chrono = std::chrono;

    // start recording time
    auto startTime = chrono::system_clock::now();

    // execute function
    //     TODO: write template deduction guide for void 
    Result result = void_invoke(std::forward<Fun>(fun),
                                std::forward<Args>(args)...);

    auto endTime = chrono::system_clock::now();
    auto executionTime = endTime - startTime;

    // return function execution info
    return {result, executionTime};
}

auto generate_ints(const size_t num, const size_t limit) {
    std::vector<int> output;
    std::generate_n(std::back_inserter(output), num,
                    [limit]() {
        return rand() % limit;
    });
    return output;
}

int main() {
    namespace chrono = std::chrono;

    auto info = record_execution([] {
        std::this_thread::sleep_for(chrono::milliseconds(1'000));
    });
    // TODO: maybe use deduction guide to make this return the withheld value
    auto result = info.get_result();

    std::cout << "result: " << info.get_result() << "\n";
    std::cout << "time elapsed: " << 
        chrono::duration_cast<chrono::milliseconds>(
            info.get_execution_time()
        ).count() << "\n";

    return 0;
}

/* int main() { */
/*     srand(time(NULL)); */

/*     const auto num = 10'000'000; */
/*     auto ints = std::async( */
/*         record_duration( */
/*             generate_ints(num, 100) */
/*         ) */
/*     ); */
/*     auto other_ints = std::async( */
/*         record_duration( */
/*             generate_ints(num, 100) */
/*         ) */
/*     ); */

/*     const auto sum = std::accumulate(std::begin(ints), std::end(ints), 0); */
/*     const auto other_sum = std::accumulate(std::begin(other_ints), std::end(other_ints), 0); */

/*     std::cout << sum << '\n'; */
/*     std::cout << other_sum << '\n'; */

/*     return 0; */
/* } */
