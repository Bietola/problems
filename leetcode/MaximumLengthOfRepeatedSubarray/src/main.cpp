#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
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
// ranges
#define RN(_RANGE) begin(_RANGE), end(_RANGE)
#define RNF(_CNTR, _START, _FINISH) for (int _CNTR = _START; _CNTR < _FINISH; ++_CNTR)
#define RNF2(_CNTR1, _START1, _FINISH1, _CNTR2, _START2, _FINISH2) \
    for (int _CNTR1 = _START1, _CNTR2 = _START2; \
         _CNTR1 < _FINISH1 && _CNTR2 < _FINISH2; \
         ++_CNTR1, ++_CNTR2)
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

int solve(const vi& a, const vi& b) {
    int maxLen = 0;
    RNF (ai, 0, a.size()) {
        RNF (bi, 0, b.size()) {
            if (a[ai] == b[bi]) {
                int candidate = 0;
                RNF2 (aii, ai, a.size(),
                      bii, bi, b.size()) {
                    if (a[aii] != b[bii])
                        break;
                    else
                        ++candidate;
                }
                if (candidate > maxLen) maxLen = candidate;
            }
        }
    }
    return maxLen;
}

int main() {
    cout << solve({1, 2, 3, 2, 1}, {3, 2, 1, 4, 7}) << endl;

    return 0;
}
