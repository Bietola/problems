#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <numeric>

using namespace std;

// primitive types
using ll = long long;
// vectors
template <class T> using v = vector<T>;
using vi = vector<int>;
using vll = vector<long long>;
using vd = vector<double>;
template <class T> using vv = vector<vector<T>>;
using vvi = vector<vector<int>>;
using vvll = vector<vector<long long>>;
using vvd = vector<vector<double>>;
// iteration
#define RNGF(_VAR, _START, _FINISH)  for (int _VAR = _START; _VAR < _FINISH; ++_VAR)
#define FORJ(_START, _FINISH) RNGF(j, _START, _FINISH)
#define FORI(_START, _FINISH) RNGF(i, _START, _FINISH)

// SOLVES PROBLEM
double solve(int N, int K, int r, int c) {
    // utility
    static array<pair<int, int>, 8> moves = {
        pair<double, double>{-1, -2},
        pair<double, double>{-2, -1},
        pair<double, double>{1, -2},
        pair<double, double>{2, -1},
        pair<double, double>{-2, 1},
        pair<double, double>{-1, 2},
        pair<double, double>{2, 1},
        pair<double, double>{1, 2}
    };
    auto iob = [N] (int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    };

    // chessboard
    vvd board(N, vd(N, 1));

    // progressively update board (dynamic programming)
    FORJ (0, K) {
        vvd newboard(N, vd(N, 0));
        RNGF (x, 0, N) {
            RNGF (y, 0, N) {
                newboard[x][y] = accumulate(begin(moves), end(moves), 0.0,
                    [&] (double sum, const auto& mv) {
                        auto mx = mv.first; 
                        auto my = mv.second; 
                        auto nx = x + mx;
                        auto ny = y + my;
                        if (iob(nx, ny))
                            return sum + board[nx][ny];
                        else
                            return sum;
                    }
                ) / 8;
                cout << newboard[x][y] << "; ";
            }
            cout << endl;
        }
        board = newboard;
    }

    // return answer
    return board[r][c];
}

main() {
    int N, K, r, c;
    cin >> N >> K >> r >> c;

    auto solution = solve(N, K, r, c);
    cout << solution << endl;

    return 0;
}
