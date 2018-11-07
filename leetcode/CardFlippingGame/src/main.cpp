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

int solve(const vi& fronts, const vi& backs) {
    mxhi pq;
    for (int ele : { 1, 2, 3, 4, 5, 6 }){
        pq.push(ele);
    }

    while (!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
}

int main() {
    solve({1, 2, 3}, {11, 12, 13});

    return 0;
}
