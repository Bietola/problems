#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <limits>

using namespace std;

// containers
using vi = vector<int>;
using mxhi = priority_queue<int>;
using mnhi = priority_queue<int, vi, greater<int>>;
// math
int mean(int lhs, int rhs) {
    return (lhs + rhs) / 2;
}
// algorithms
#define RN(_RANGE) begin(_RANGE), end(_RANGE)
// functional
const auto gti = greater<int>();
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

// SOLUTION
int solve(const vi& fronts, const vi& backs) {
    vi heap;

    copy(RN(fronts), back_inserter(heap));
    copy(RN(backs), back_inserter(heap));

    make_heap(RN(heap), gti);
}

// MAIN
int main() {
    solve({1, 2, 3}, {11, 12, 13});

    mxhi heap;
    vi v = {1, 2, 3, 4};

    while (!heap.empty()) {
        cout << heap.top() << endl;
        heap.pop();
    }

    return 0;
}
