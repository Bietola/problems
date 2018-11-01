#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

ll digitsum(ll n, ll acc = 0) {
    if (n == 0) return acc;
    else return digitsum(n / 10, acc + n % 10);
}

pll solve(ll n, ll d) {
    queue<pll> q;
    unordered_map<ll, ll> m;
    q.emplace(n, 0);

    ll target = ((n % 3 == 0 && d % 3 == 0) ? 3 : 1);

    while (!q.empty()) {
        ll n = q.front().first;
        ll ops = q.front().second;
        q.pop();

        if (n < 10) {
            if (n == target) {
                return { n, ops };
            }
            else if (m.find(n) == m.end()) {
                m[n] = ops;
                q.emplace(n + d, ops + 1);
            }
        }
        else {
            q.emplace(digitsum(n), ops + 1);
            q.emplace(n + d, ops + 1);
        }
    }
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
