#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

class Solution {
public:
    int minFallingPathSum(const vector<vector<int>>& A) {
        vector<ll> output;
        findSums(A, output);
    }
    void findSums(const vector<vector<int>>& input,
                  const vector<int>& output,
                  size_t crVecPos = 0,
                  size_t crPos = 0) {
        // some aliases
        auto& crVec = input[crVecPos];
        auto crEle  = crVec[crPos];

        // base case
        if (crVecPos == input.size() - 1) {
            crEle;
        }

        // left sum
        if (leftPos >= 0)
            output.push_back(crEle + solve(input, crVecPos + 1, crPos - 1));
        // center sum
        centerSum = crEle + solve(input, crVecPos + 1, crPos);
        // right sum 
        if (rightPos < crVec.size()) 
            output.push_back(crEle + solve(input, crVecPos + 1, crPos + 1));
    }
};

vector<vector<int>> parse(vector<vector<int>>& acc,
                          vector<int>& currAcc,
                          const string& str,
                          bool endFlag) {
    if (str.front() == ']') {
        if (endFlag)
            return acc;
        else {
            acc.push_back(currAcc);
            currAcc = {};
        }
    }
    // not a ]: reset *endFlag*
    else {
        endFlag = false;
        if (isdigit(str.front())) {
            currAcc.push_back(int(str.front() - '0'));
        }
        else if (str.empty()) {
            assert(false);
        }
    }
    // continue
    return parse(acc, currAcc, str.substr(1), endFlag);
}

auto parse(const string& str) {
    vector<vector<int>> acc;
    vector<int> firstAcc;
    return parse(acc, firstAcc, str, false);
}

int main() {
    auto vv = parse("[[1]]");

    for (const auto& v : vv) {
        for (const auto& e : v) {
            cout << e << ", ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
