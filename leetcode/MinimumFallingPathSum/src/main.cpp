#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

using ll = long long;

void solve(const vector<vector<ll>>& input,
           vector<ll>& output,
           vector<vector<ll>>::iterator vecItr,
           vector<ll>::iterator itr,
           ll acc) {
    if (vecItr == end(input)) {
        output.push_back(acc);
    }
    else {
        // center
        solve(input, output, next(vecItr), itr, acc + *itr);
        // left
        if (prev(itr) != rend(/*TODO*/))
            solve(input, output, next(vecItr), prev(itr), acc + *itr);
        // right
        if (next(itr) != end(/*TODO*/))
            solve(input, output, next(vecItr), next(itr), acc + *itr);
    }
}

void solve(const vector<vector<ll>>& input,
           vector<ll>& output) {
    return solve(input, output, begin(input), begin(input.front()), 0L);
}

int main() {
    vector<vector<ll>> input = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<ll> output;
    solve(input, output);

    for (const auto& row : output) {
        for (const auto& ele : row) {
            cout << ele << ", ";
        }
        cout << "\n";
    }

    return 0;
}
