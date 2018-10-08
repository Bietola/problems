#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>
#include <numeric>
#include <thread>
#include <chrono>
#include <optional>

struct empty_type {};

template <class Data> 
struct void_holder {
    private:
        Data _data;

    public:
        void_holder<Data>(Data&& data): _data(std::forward<Data>(data)) {}

        Data get() const { return _data; }

        const bool is_void() const { return false; }

        operator Data() const { return _data; }
};

template <class T>
std::ostream& operator<<(std::ostream& ostream, const void_holder<T>& toPrint) {
    if constexpr(std::is_void_v<T>) {
        ostream << "{void}";
    }
    else {
        ostream << toPrint.get();
    }
    return ostream;
}

template <>
struct void_holder<void> {
    public:
        void_holder<void>(...) {}

        const bool is_void() const { return true; }
};

std::ostream& operator<<(std::ostream& ostream, const void_holder<void>&) {
    ostream << "{void}";
    return ostream;
}

template <class Fun, class... Args,
          class Result = std::invoke_result_t<Fun, Args...>>
void_holder<Result> void_invoke(Fun&& fun, Args&&... args) {
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

// TODO: make it hold a void_holder insted of the direct result type
template <class Result, class TimeRep = double>
struct execution_info {
    private:
        using ResultOrVoid = void_holder<Result>;

        ResultOrVoid _result;
        std::chrono::duration<TimeRep> _execution_time;

    public:
        execution_info(const ResultOrVoid& result, const std::chrono::duration<TimeRep>& execution_time): _result(result), _execution_time(execution_time) {}

        void_holder<Result> get_result() const { return _result; }
        auto get_execution_time() const { return _execution_time; }
};

template <class Fun, class... Args,
          class Result = std::invoke_result_t<Fun, Args...>>
execution_info<Result> record_time(Fun&& fun, Args&&... args) {
    namespace chrono = std::chrono;

    // start recording time
    auto startTime = chrono::system_clock::now();

    // execute function
    //     TODO: write template deduction guide for void 
    void_holder<Result> result = void_invoke(std::forward<Fun>(fun),
                                             std::forward<Args>(args)...);

    auto endTime = chrono::system_clock::now();
    auto executionTime = endTime - startTime;

    // return function execution info
    return execution_info<Result>(result, executionTime);
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

    auto info = record_time([] {
        std::this_thread::sleep_for(chrono::milliseconds(1'000));
        return 10;
    });
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
