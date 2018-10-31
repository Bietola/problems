#include <iostream>
#include <utility>
#include <queue>

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
pll solve(ll n, ll d, ll target, ll depth, queue<pll>& q) {
    // visit node
    if (n == target)
        return { target,  depth };

    // add children to queue
    q.emplace(n + d, depth + 1);
    q.emplace(digitsum(n), depth + 1);

    // visit next in queue
    auto nextNode = q.front(); q.pop();
    return solve(nextNode.first, d, target, nextNode.second, q);
}

pll solve(ll n, ll d, ll target) {
    queue<pll> q = {};

    return solve(n, d, target, 0, q);
}

// MAIN
int main() {
    uint T;
    cin >> T;

    for(uint j = 0; j < T; ++j) {
        ll n, d;
        cin >> n >> d;
        auto solution = solve(n, d, 1);
        cout << solution.first << " " << solution.second << "\n";
    }

    return 0;
}
