#pragma once

#include <vector>
#include <optional>

void combs(const std::vector<int>& alphabet, int target,
           std::vector<std::vector<int>>& result,
           std::pair<size_t, size_t> targetRange = {1, std::numeric_limits<size_t>::max()},
           const std::vector<int>& current = {}) {
    if(target < 0 || current.size() > targetRange.second) {
        return;
    }
    else if(!target) {
        if(current.size() >= targetRange.first) result.push_back(current);
        return;
    }
    else {
        for(auto itr = alphabet.cbegin(); itr != alphabet.cend(); ++itr) {
            std::decay_t<decltype(alphabet)> newAlphabet;
            std::copy(itr, alphabet.cend(), std::back_inserter(newAlphabet));

            auto newCurrent  = current;
            const auto& sym = *itr;
            newCurrent.push_back(sym);

            combs(newAlphabet, target - sym, result, targetRange, newCurrent);
        }
    }
}
