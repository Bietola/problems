#include <range/v3/all.hpp>
#include <iostream>

using namespace ranges;

int main() {
    auto things =
        view::iota(int(1), int(10)) |
            view::group_by([] (auto lhs, auto rhs) {
                return lhs % 3 == rhs % 3;
            });

    std::cout << things << std::endl;

    return 0;
}

