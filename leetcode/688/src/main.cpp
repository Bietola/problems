#include <iostream>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

// vectors
template <class T> using vv = vector<vector<T>>;
using vvi = vv<int>;
// iteration
#define RNGF(_VAR, _START, _FINISH)  for (int _VAR = _START; _VAR < _FINISH; ++_VAR)
#define FORJ(_START, _FINISH) RNGF(j, _START, _FINISH)
#define FORI(_START, _FINISH) RNGF(i, _START, _FINISH)

// SOLVES PROBLEM
double solve(int N, int K, int r, int c) {
    // utility
    static array<pair<int, int>, 8> moves = {
        pair<int, int>{-1, -2},
        pair<int, int>{-2, -1},
        pair<int, int>{1, -2},
        pair<int, int>{2, -1},
        pair<int, int>{-2, 1},
        pair<int, int>{-1, 2},
        pair<int, int>{2, 1},
        pair<int, int>{1, 2}
    };
    auto iob = [N] (int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    };

    // chessboard
    vvi board;
    board.resize(N);
    FORJ (0, N) board[j].resize(N);

    // construct initial board
    FORJ (0, N) {
        FORI (0, N) {
            if (j == 0 || i == 0 || j == N - 1 || i == N - 1) board[j][i] = 2;
            else if ((j == 1 || j == N - 2) && (i == 1 || i == N - 2)) board[j][i] = 4;
            else if (j == 1 || i == 1 || j == N - 2 || i == N - 2) board[j][i] = 6;
            else board[j][i] = 8;
        }
    }

    // progressively update board (dynamic programming)
    FORJ (0, K - 1) {
        vvi newboard;
        newboard.resize(N);
        FORJ (0, N) newboard[j].resize(N);
        RNGF (x, 0, N) {
            RNGF (y, 0, N) {
                newboard[x][y] = 0;
                for (const auto& mv : moves) {
                    auto mx = mv.first; 
                    auto my = mv.second; 
                    auto nx = x + mx;
                    auto ny = y + my;
                    if (iob(nx, ny)) {
                        newboard[x][y] += board[nx][ny];
                    }
                }
                cout << newboard[x][y] << "; ";
            }
            cout << endl;
        }
        board = newboard;
    }

    // return answer
    return double(board[r][c])/pow(8, K);
}

main() {
    int N, K, r, c;
    cin >> N >> K >> r >> c;

    auto solution = solve(N, K, r, c);
    cout << solution << endl;

    return 0;
}
