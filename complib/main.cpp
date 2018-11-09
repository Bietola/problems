+include pprint
+include loops

#include <iostream>
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

void findIsland(const vvi& board, int sx, int sy,
                set<pair<int, int>>& output) {
    auto dirs = array<pair<int, int>, 4>{ { {0, -1}, {1, 0}, {0, 1}, {-1, 0} } };

    for (const auto& dir : dirs) {
        int nx = sx + dir.first;
        int ny = sy + dir.second;
        if (iob(board, nx, ny) &&
                output.find({ nx, ny }) == end(output) && board[ny][nx] == 1) {
            output.emplace(nx, ny);
            findIsland(board, nx, ny, output);
        }
    }
}

int solve(const vvi& board)  {
    // find islands
    set<pair<int, int>> island1, island2;
    FORY (0, board.size()) {
        FORX (0, board[y].size()) {
            if (board[y][x] == 1) {
                if (island1.empty()) {
                    findIsland(board, x, y, island1);
                }
                else if(island1.find({ x, y }) == end(island1)) {
                    findIsland(board, x, y, island2);
                    goto endloop;
                }
            }
        }
    }
endloop:
    for (const auto& ele : island1)
        cout << ele.first << ", " << ele.second << "| ";
    cout << endl;
    for (const auto& ele : island2)
        cout << ele.first << ", " << ele.second << "| ";
    cout << endl;
}

int main() {
    vvi board;

    string line;
    while (getline(cin, line)) {
        vi row;
        stringstream ss;
        ss << line;
        int n;
        while (ss >> n) {
            row.push_back(n);
        }
        board.push_back(row);
    }

    solve(board);

    return 0;
}
