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

bool solve(const string& input, int state = 0) {
    if (input.empty()) {
        return state == 2;
    }

    auto c = input.front();
    auto tale = input.substr(1);
    if (state == 0) {
        if (c == '1') {
            return solve(tale, 1);
        }
        else if (c == '0') {
            return solve(tale, 2);
        }
    } 
    else if (state == 1) {
        if (c == '1') {
            return solve(tale, 0);
        }
        else if (c == '0') {
            return solve(tale, 0);
        }
    }
    else if (state == 2) {
        if (c == '1') {
            return solve(tale, 1);
        }
        else if (c == '0') {
            return solve(tale, 2);
        }
    }
}

string toString(const vi& v) {
    return accumulate(RN(v), string(""), [] (auto acc, auto ele) {
        return acc + char(ele + '0');
    });
}

int main() {

    return 0;
}
