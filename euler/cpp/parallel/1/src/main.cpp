#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
#include <thread>
#include <chrono>
#include <optional>

#include "utils.h"

struct empty_type {};

std::ostream& operator<<(std::ostream& ostream, const empty_type&) {
    ostream << "{empty_type}";
    return ostream;
}

template <class Data, class TimeRep = double>
struct execution_info {
    private:
        std::conditional_t<
            std::is_void_v<Data>, empty_type, Data
        > _data;
        std::chrono::duration<TimeRep> _elapsed_time;

    public:
        auto get_data() const {
            if constexpr(std::is_void_v<Data>) {
                return empty_type{};
            }
            else {
                return _data;
            }
        }
        const auto get_elapsed_time() const { return _elapsed_time; }

        operator Data() { return get_data(); }
};

template <class Func, class TimeRep, class... Args>
auto record_time(Func func, Args&&... args)
        -> execution_info<decltype(func(std::forward<Args>(args)...)), TimeRep> {
    // start clock
    auto start = std::chrono::system_clock::now();

    // tmp
    auto funcWargs = [
        &func,
        args = std::make_tuple(std::forward<Args>(args)...)
    ] () {
        return std::apply(func, args);
    };

    // get return type of function
    using FuncRet = decltype(func(std::forward<Args>(args)...));

    // function that stops clock and returns elapsed time
    auto calc_elapsed_time = [&start] {
        auto end = std::chrono::system_clock::now();
        auto elapsedTime = end - start;
        return elapsedTime;
    };

    // actually call function
    if constexpr(std::is_void_v<FuncRet>) {
        funcWargs();
    }
    else {
        using RetVal = decltype(funcWargs());
        RetVal retVal = funcWargs();
        return std::make_pair(std::optional<RetVal>(retVal), calc_elapsed_time());
    }
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
    execution_info<empty_type, long long> info = record_time([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
    });
    std::cout << "result: " << info.get_data() << "\n";
    std::cout << "time elapsed: " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(
            info.get_elapsed_time()
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
