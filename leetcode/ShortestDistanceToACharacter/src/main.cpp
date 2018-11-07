#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>

using namespace std;

// containers
using vi = vector<int>;
// math
int mean(int lhs, int rhs) {
    return (lhs + rhs) / 2;
}
// printing
template <class T>
ostream& operator<<(ostream& ostr, const vector<T>& toPrint) {
    ostr << "[";
    for (const auto& ele : toPrint) {
        ostr << ele << ", ";
    }
    ostr << "]";
    return ostr;
}

void solve(string s, char c, vi& output, int idx = 0, int dist = -1) {
    if (s.empty()) {
        for (int j = idx - 1; j > dist; --j)
            output[j] = j - dist;
        return;
    }
    if (s.front() == c) {
        for (int j = idx - 1; j > dist; --j) {
            if (dist != -1 && j <= mean(dist, idx))
                output[j] = j - dist;
            else
                output[j] = idx - j;
        }
        dist = idx;
    }

    return solve(s.substr(1), c, output, idx + 1, dist);
}

int main() {
    string s;
    char c;
    cin >> s >> c;

    vi output;
    output.resize(s.size());
    solve(s, c, output);

    cout << output << endl;

    return 0;
}
