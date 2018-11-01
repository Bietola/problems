#include <iostream>
#include <utility>
#include <queue>
#include <array>

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
pll solve(ll n, ll d, ll target, ll depth,
          queue<pll>& q, array<bool, 9>& visited) {
    // visit node
    if (n == target) {
        return { target, depth };
    }

    // add children to queue
    if (n >= 10) {
        q.emplace(digitsum(n), depth + 1);
        q.emplace(n + d, depth + 1);
    } 
    else if (!visited[n - 1]) {
        visited[n - 1] = true;
        q.emplace(n + d, depth + 1);
    }

    // visit next in queue
    auto nextNode = q.front(); q.pop();
    return solve(nextNode.first, d, target, nextNode.second, q, visited);
}

pll solve(ll n, ll d) {
    queue<pll> q = {};
    array<bool, 9> visited = { false };
    ll target = ((n % 3 == 0) && (d % 3 == 0) ? 3 : 1);

    return solve(n, d, target, 0, q, visited);
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
