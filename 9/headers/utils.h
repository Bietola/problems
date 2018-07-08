#pragma once

#include <vector>
#include <optional>

void combs(const std::vector<int>& alphabet, int target,
           std::vector<std::vector<int>>& result,
           // default arguments
           std::pair<size_t, size_t> targetRange, 
           const std::vector<int>& current,
           // internal arguments
           const int originalTarget) {
    // invalid combination
    if(target <= 0 || current.size() > targetRange.second) {
        return;
    }
    // potential valid combination
    else if(current.size() == targetRange.second - 1) {
        // filter out duplicates
        if(target >= originalTarget - target) {
            auto newCurrent = current;
            newCurrent.push_back(target);
            result.push_back(newCurrent);
        }
        return;
    }
    // recursive step
    else {
        for(auto itr = alphabet.cbegin(); itr != alphabet.cend(); ++itr) {
            std::decay_t<decltype(alphabet)> newAlphabet;
            std::copy(itr, alphabet.cend(), std::back_inserter(newAlphabet));

            auto newCurrent  = current;
            const auto& sym = *itr;
            newCurrent.push_back(sym);

            combs(newAlphabet, target - sym, result, targetRange, newCurrent, originalTarget);
        }
    }
}

void combs(const std::vector<int>& alphabet, int target,
           std::vector<std::vector<int>>& result,
           std::pair<size_t, size_t> targetRange = {1, std::numeric_limits<size_t>::max()},
           const std::vector<int>& current = {}) {
    combs(alphabet, target, result, targetRange, current, target);
}

