#include <iostream>
#include <unordered_set>
#include <set>
#include <sstream>
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
using vvi = vector<vi>;
using pi = pair<int, int>;
using vpi = vector<pi>;
// math
int mean(int lhs, int rhs) {
    return (lhs + rhs) / 2;
}
constexpr const int intinf = numeric_limits<int>::max();
// ranges
#define RN(_RANGE) begin(_RANGE), end(_RANGE)
// loops
#define FORJ(_START, _FINISH) for (int j = _START; j < _FINISH; ++j)
#define FORK(_START, _FINISH) for (int k = _START; k < _FINISH; ++k)
#define FORX(_START, _FINISH) for (int x = _START; x < _FINISH; ++x)
#define FORY(_START, _FINISH) for (int y = _START; y < _FINISH; ++y)

// matrices
template <class Board>
bool iob(int x, int y, const Board& board) {
    return x >= 0 && y >= 0 && x < board.size() && y < board.size();
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

using Island = set<pi>;

// returns snake distance
int snakeDistance(const pi& lhs, const pi& rhs) {
    return abs(lhs.first - rhs.first) + abs(lhs.second - rhs.second) - 1;
}

// finds an island
void findIsland(Island& output, const vvi& board, int sx, int sy) {
    static vpi dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    output.emplace(sx, sy);

    for (const auto& dir : dirs) {
        int nx = dir.first + sx;
        int ny = dir.second + sy;
        if (iob(nx, ny, board) && !output.count({ nx, ny }) && board[ny][nx] == 1)
            findIsland(output, board, nx, ny);
    }
}

// returns minimum number of land patches needed for connection
int solve(const vvi& board) {
    Island firstIsland, secondIsland;
    FORY (0, board.size()) {
        FORX (0, board[0].size()) {
            auto ele = board[y][x];
            if (firstIsland.empty() && ele == 1) {
                findIsland(firstIsland, board, x, y);
            }
            else if (!firstIsland.count({ x, y }) && ele == 1) {
                findIsland(secondIsland, board, x, y);
                goto endloop;
            }
        }
    }
endloop:
    int ret = intinf;
    for (const auto& sq1 : firstIsland) {
        for (const auto& sq2 : secondIsland) {
            auto dist = snakeDistance(sq1, sq2);
            if (dist < ret) ret = dist;
        }
    }
    return ret;
}

int main() {
    vvi board;
    string line;
    while(getline(cin, line)) {
        stringstream ss;
        ss << line;
        int ele;
        vi row;
        while (ss >> ele) {
            row.push_back(ele);
        }
        board.push_back(row);
    }

    cout << solve(board) << endl;

    return 0;
}
