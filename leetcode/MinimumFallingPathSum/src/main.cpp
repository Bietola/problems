#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <limits>

using namespace std;

using ll = long long;
template <class T, size_t size> using a = array<T, size>;
template <class T, size_t size1, size_t size2> using a2d = array<array<T, size1>, size2>;

/* const constexpr static int inf = numeric_limits<int>::max(); */
const constexpr static int inf = numeric_limits<int>::max();

template <size_t size>
int solve(a2d<int, size, size>& input) {
    for (int rowi = input.size() - 2; rowi >= 0; --rowi) {
        auto& row = input[rowi];
        auto& nextRow = input[rowi + 1];
        for (size_t elei = 0; elei < row.size(); ++elei) {
            auto& ele = row[elei];
            auto leftEle = (elei == 0 ? inf : nextRow[elei - 1]);
            auto rightEle = (elei == row.size() - 1 ? inf : nextRow[elei + 1]);
            auto centerEle = nextRow[elei];
            ele += min(min(leftEle, rightEle), centerEle);
        }
    }
    const auto& firstRow = input[0];
    return *min_element(begin(firstRow), end(firstRow));
}

main() {
    a2d<int, 4, 4> input = {
        63, 70, 79, 18,
        90, 16, -10, 32,
        100, 84, 59, -84,
        23, -3, 26, 69
    };

    /* a2d<int, 3, 3> input = { */
    /*     1, 2, 3, */
    /*     4, 5, 6, */
    /*     7, 8, 9 */
    /* }; */

    int solution = solve(input);
    cout << "minimum falling sum: " << solution << endl;

    return 0;
}
