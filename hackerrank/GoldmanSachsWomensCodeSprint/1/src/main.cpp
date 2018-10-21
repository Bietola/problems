#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

int calculateSharesPrice(const std::vector<std::pair<int, int>>& sp,
                         const int number) {
    // find subrange of elements equal to number
    struct Comp {
        bool operator()(const std::pair<int, int>& ele, int value) const {
            return ele.first == value;
        }
        bool operator()(int value, const std::pair<int, int>& ele) const {
            return ele.first == value;
        }
    };
    const auto range = std::equal_range(std::begin(sp), std::end(sp),
                                        number, Comp{});
    const auto rnBeg = range.first;
    const auto rnEnd = range.second;

    // if a subrange exists, just select the last element,
    // since it is the largest
    if(rnBeg != rnEnd) {
        return std::prev(rnEnd)->second;
    }
    // if the subrange is empty and at the end of the initial range,
    // then the last element of the initial range is the largest of
    // the elements less than number, since they all are
    else if(rnEnd == std::end(sp)) {
        return std::prev(rnEnd)->second;
    }
    // TODO
    else if(rnBeg == std::begin(sp)) {
        assert(false && "there does not exist an element that is less than number");
    }
    // TODO
    else {
        return std::prev(rnBeg)->second;
    }
}

std::vector<int> 
computePrices(const std::vector<int>& s, const std::vector<int>& p,
              const std::vector<int>& q) {
    // assert some stuff
    assert(s.size() == p.size());

    // put s and p together
    std::vector<std::pair<int, int>> sp;
    sp.reserve(s.size());
    std::transform(std::begin(s), std::end(s),
                   std::begin(p),
                   std::back_inserter(sp),
                   [](int sEle, int pEle) {
        return std::make_pair(sEle, pEle);
    });

    // sort sp
    std::sort(std::begin(sp), std::end(sp),
              [] (const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
    
    // calculate answer to problem
    std::vector<int> results;
    results.reserve(sp.size());
    std::transform(std::begin(q), std::end(q),
                   std::back_inserter(results),
                   [&sp] (const auto value) {
        return calculateSharesPrice(sp, value);
    });
    return results;
}

int main() {
    std::ifstream inFile ("assets/input");
    std::ofstream outFile("assets/output");

    std::vector<int> s, p, q;
    int n, k;
    inFile >> n;
    for(size_t j = 0; j < n; ++j) {
        int sEle;
        inFile >> sEle;
        s.push_back(sEle);
    }
    for(size_t j = 0; j < n; ++j) {
        int pEle;
        inFile >> pEle;
        p.push_back(pEle);
    }
    inFile >> k;
    for(size_t j = 0; j < k; ++j) {
        int qEle;
        inFile >> qEle;
        q.push_back(qEle);
    }

    auto results = computePrices(s, p, q);

    for(const auto& ele : results) {
        std::cout << ele << ", ";
    }
    std::cout << "\n";

    inFile.close();
    outFile.close();

    return 0;
}
