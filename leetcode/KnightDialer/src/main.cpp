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
#define RNF(_VAR, _START, _FINISH)  for (int _VAR = _START; _VAR < _FINISH; ++_VAR)
#define FORJ(_START, _FINISH) RNF(j, _START, _FINISH)
#define FORI(_START, _FINISH) RNF(i, _START, _FINISH)
// algorithms
#define RN(_CONTAINER) begin(_CONTAINER), end(_CONTAINER)

// constants
#define MOD 1000000007ll

// SOLVES PROBLEM
ll solve(int N) {
    // board
    vvll board = {
        { 1,  1,  1},
        { 1,  1,  1},
        { 1,  1,  1},
        {-1,  1, -1}
    };

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
    auto iob = [&board] (int x, int y) {
        int Nx = 3;
        int Ny = 4;
        return (x >= 0 && x < Nx && y >= 0 && y < Ny) && board[y][x] != -1;
    };

    // build board
    auto newboard = board;
    FORJ (0, N - 1) { 
        cout << "BOARD " << j << "\n";
        RNF (y, 0, 4) {
            RNF (x, 0, 3) {
                if (board[y][x] != -1) {
                    newboard[y][x] = accumulate(RN(moves), 0ll,
                        [&] (ll sum, const auto& mv) {
                            auto nx = x + mv.first;
                            auto ny = y + mv.second;
                            if (iob(nx, ny)) 
                                return (sum + board[ny][nx]) % MOD;
                            else
                                return sum;
                        }
                    );
                    cout << newboard[y][x] << ", ";
                }
            }
            cout << endl;
        }
        board = newboard;
        cout << endl;
    }

    // RETURN
    ll sum = 0;
    RNF (y, 0, 4) {
        RNF (x, 0, 3) {
            if (board[y][x] != -1) sum = (sum + board[y][x]) % MOD;
        }
    }
    return sum;
}

main() {
    int N;
    cin >> N;

    auto solution = solve(N);
    cout << "SOLUTION: " << solution << endl;

    return 0;
}
