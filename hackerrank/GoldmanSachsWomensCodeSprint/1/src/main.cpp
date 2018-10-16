#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int calculateSharesPrice(const std::vector<int>& s, const std::vector<int>& p,
                         const int number) {
    auto itrMax = std::end(s);
    for(auto itr = std::begin(s); itr != std::end(s); ++itr) {
        if(*itr <= number &&
           *itr > (itrMax != std::end(s) ? *itrMax : 0))
            itrMax = itr;
    }
    if(itrMax == std::end(s)) {
        assert(false);
        return -1;
    }
    else
        return p[std::distance(std::begin(s), itrMax)];
}

std::vector<int> computePrices(const std::vector<int>& s, const std::vector<int>& p,
                               const std::vector<int>& q) {
    std::vector<int> results;
    results.reserve(s.size());
    
    std::transform(std::begin(q), std::end(q),
                   std::back_inserter(results),
                   [&s, &p] (const auto value) {
        return calculateSharesPrice(s, p, value);
    });

    return results;
}

int main() {
    std::cout << "Hello world!\n";

    return 0;
}
