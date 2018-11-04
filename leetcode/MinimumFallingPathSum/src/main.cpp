#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>

using namespace std;

using ll = long long;

void getFallingSums(const vector<vector<ll>>& input,
                    vector<ll>& output,
                    vector<vector<ll>>::const_iterator vecItr,
                    vector<ll>::const_iterator itr,
                    ll acc) {
    auto newAcc = acc + *itr;

    if (vecItr == prev(cend(input))) {
        output.push_back(newAcc);
    }
    else {
        // construct next things
        auto nextVecItr = next(vecItr);
        auto nextItr = cbegin(*next(vecItr)) + distance(cbegin(*vecItr), itr);
        // recurse center
        getFallingSums(input, output, next(vecItr), nextItr, newAcc);
        // recurse left
        if (prev(nextItr) != prev(cbegin(*nextVecItr)))
            getFallingSums(input, output, next(vecItr), prev(nextItr), newAcc);
        // recurse right
        if (next(nextItr) != cend(*nextVecItr))
            getFallingSums(input, output, next(vecItr), next(nextItr), newAcc);
    }
}

ll solve(const vector<vector<ll>>& input) {
    // get all sums
    vector<ll> sums;
    const auto& toprow = *cbegin(input);
    for (auto itr = cbegin(toprow); itr != cend(toprow); ++itr) {
        getFallingSums(input, sums, cbegin(input), itr, 0ll);
    }

    /* // DB */
    /* for (const auto& ele : sums) { */
    /*     cout << ele << ", "; */
    /* } */
    /* cout << endl; */
    /* // END DB */

    // return minimum
    return *min_element(cbegin(sums), cend(sums));
}

int main() {
    vector<vector<ll>> input = {
        {63, 70, 79, 18},
        {90, 16, -10, 32},
        {100, 84, 59, -84},
        {23, -3, 26, 69}
    };

    cout << "minimum falling sum: " << solve(input) << "\n";

    return 0;
}
