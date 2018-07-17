#include <cassert> 
#include <iostream>
#include <initializer_list>
#include <range/v3/all.hpp>

using namespace ranges;

auto getDivs(const int from, const int to, const std::initializer_list<int>& divs) {
    return view::iota(from, to) |
        view::filter([&divs](const auto dividend) {
            return any_of(view::all(divs), [dividend](const auto divisor) {
                assert(divisor != 0);
                return dividend % divisor == 0;
            });
        });
}

int main() {
    std::cout << accumulate(getDivs(0, 1000, {3, 5}), 0) << std::endl;

    return 0;
}
