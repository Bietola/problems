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
    
    // do it!
    auto resPos = std::accumulate(
        num.begin() + RANGE, num.end(),
        std::make_pair(num.begin(), num.begin()),
        [] (const auto max, const auto ele) {
            return ele > *max.second ?
                std::make_pair(max.first + 1, max.first) :
                std::make_pair(max.first + 1, max.second);
        }
    );

    // exit
    return 0;
}
