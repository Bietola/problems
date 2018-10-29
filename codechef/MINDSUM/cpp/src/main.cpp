#include <iostream>
#include <utility>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using uint = unsigned int;

const uint MAX_DEPTH = 50;

// outputs digitsum
auto digitsum(ll num, ll sum = 0) {
    if (num == 0)
        return sum;
    else
        return digitsum(num / 10, sum + (num % 10));
}

// prints: minimum value, minimum num of ops
pll solve(ll n, ll d, uint depth = 0) {
    if (depth > MAX_DEPTH || n == 1) {
        /* cout << n << ", " << depth << endl; */
        return { n, depth }; // depth is num of ops
    }
    else {
        pll dsumBranch = { n, depth };
        // only take digitsum branch if it modifies n
        if (auto cache = digitsum(n); cache != n)
            dsumBranch = solve(cache, d, depth + 1);
        return min(solve(n + d, d, depth + 1), dsumBranch,
                   [] (const auto& lhs, const auto& rhs) {
                       return lhs.first < rhs.first ||
                                  (lhs.first == rhs.first &&
                                   lhs.second < rhs.second);
                   });
    }
}

// MAIN
int main() {
    uint T;
    cin >> T;

    for(uint j = 0; j < T; ++j) {
        ll n, d;
        cin >> n >> d;
        auto solution = solve(n, d);
        cout << solution.first << " " << solution.second << "\n";
    }

    return 0;
}
