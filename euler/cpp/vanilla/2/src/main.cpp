#include <iostream>
#include <range/v3/all.hpp>

using namespace ranges;

auto fibonacci() {
    return view::concat(
        view::single(1), view::single(2),
        view::generate([s1 = 1L, s2 = 2L] () mutable {
            s1 = std::exchange(s2, s1 + s2);
            return s2;
        }));
}

auto fibEvenSum(long limit) {
    return accumulate(
        fibonacci() |
            view::filter([] (const auto num) {return num % 2 == 0;}) |
            view::take_while([limit] (const auto num) {return num <= limit;}),
        0L);
}

int main() {
    std::cout << fibEvenSum(4'000'000) << std::endl;

    return 0;
}
