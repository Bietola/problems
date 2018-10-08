#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <iterator>

const size_t NUM_SIZE = 1000;
const size_t RANGE = 13;

int main() {
    // take it in
    std::ifstream inf;
    try {
        inf.open("assets/input");
    }
    catch(const std::ifstream::failure& e) {
        std::cout << "ERR: " << e.what() << std::endl;
        std::terminate();
    }

    std::vector<int> num;
    num.reserve(NUM_SIZE);
    std::transform(std::istream_iterator<char>(inf),
                   std::istream_iterator<char>(),
                   std::back_inserter(num),
                   [] (auto ele) { return (int)(ele - '0'); });

    inf.close();
    
    // do it
    auto max = std::accumulate(num.begin(), num.end() - RANGE, 
                               std::make_pair(0l, num.begin()),
        [] (const auto info, const auto ele) {
            auto [max, itr] = info;
            auto candidate = std::accumulate(itr, itr + RANGE, 1l, 
                                             std::multiplies<>());
            return candidate > max ? std::make_pair(candidate, itr + 1) :
                                     std::make_pair(max,       itr + 1);
        }
    ).first;

    // print it
    std::cout << max << std::endl;

    // exit
    return 0;
}
