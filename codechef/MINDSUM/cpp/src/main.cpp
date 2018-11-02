#include <iostream>
#include <queue>
#include <map>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
using uint = unsigned int;

const uint MAX_OPS = 100'000;

ll digitsum(ll n, ll acc = 0) {
    if (n == 0) return acc;
    else return digitsum(n / 10, acc + n % 10);
}

pll solve(ll n, ll d) {
    queue<pll> q;
    map<ll, ll> m;
    q.emplace(n, 0);

    for (uint i = 0; i < MAX_OPS && !q.empty(); ++i) {
        ll n = q.front().first;
        ll ops = q.front().second;
        q.pop();

        if (m.find(n) == m.end()) {
            if (n < 10) {
                m[n] = ops;
            }
            else {
                q.emplace(digitsum(n), ops + 1);
            }
            q.emplace(n + d, ops + 1);
        }
    }
    return { m.begin()->first, m.begin()->second };
}

int main() {
    short T;
    cin >> T;

    while (T-- > 0) {
        ll n, d;
        cin >> n >> d;
        auto solution = solve(n, d);
        cout << solution.first << " " << solution.second << "\n";
    }

    return 0;
}
